#include <quix/Layout.hpp>

#include <iostream>


using namespace std;





namespace quix
{



// core
PointF Layout::operator()() const
{
	switch(mode)
	{
	case centermode:
		return center();
	case pointmode:
		return point();
	case boundsmode:
		return bounds();
	case localmode:
		throw std::logic_error("Layout::operator()(): call but mode is local");
	default:
		throw std::logic_error("mode is invalid");
	}
}

PointF Layout::operator()(int i) const
{
	if(mode == localmode)
		return local(i);
	if(childs.empty())
		return operator()();
	return place(i)();
}



PointF Layout::center(int i) const
{
	if(mode == localmode)
		return refp + size * PointF{
			(1.0f + 2.0f*(i/locn.y)) / (2.0f*locn.x),
			(1.0f + 2.0f*(i%locn.y)) / (2.0f*locn.y)
		};
	if(childs.empty())
		return center();
	return place(i).center();
}

PointF Layout::point(int i) const
{
	if(mode == localmode)
		return refp + PointF{
			size.x * (i/locn.y) / locn.x,
			size.y * (i%locn.y) / locn.y
		};
	if(childs.empty())
		return point();
	return place(i).point();
}

PointF Layout::bounds(int i) const
{
	if(mode == localmode)
		return size / locn;
	if(childs.empty())
		return bounds();
	return place(i).bounds();
}

PointF Layout::local(PointI const &p) const
{
	return refp + size * makep(
		loctype.x == first ?
			(1.0f + 2.0f*p.x) / (2.0f*locn.x) :
			(p.x + 1.0f) / (locn.x + 1.0f),
		loctype.y == first ?
			(1.0f + 2.0f*p.y) / (2.0f*locn.y) :
			(p.y + 1.0f) / (locn.y + 1.0f)
	);
}





// push
void Layout::push(int n)
{
	for(int i = 0; i < n; ++i)
		childs.push_back({ new Layout, 1.0f });
	return;
}

void Layout::push(std::vector<float> const &weights)
{
	for(int i = 0; i < (int)weights.size(); ++i)
		childs.push_back({new Layout, weights[i]});
	return;
}



void Layout::setloc(
	int xn, int yn,
	LocalType xtype, LocalType ytype
)
{
	mode = localmode;
	locn = { xn, yn };
	loctype = { xtype, ytype };
	count = locn.x * locn.y;
	return;
}

void Layout::setloc(
	PointI const &n,
	Point<LocalType> const &type
)
{
	mode = localmode;
	locn = n;
	loctype = type;
	count = locn.x*locn.y;
	return;
}



// technical
void Layout::adjust()
{
	if(mode == localmode)
	{
		count = locn.x * locn.y;
		return;
	}


	if(childs.empty())
	{
		count = 1;
		return;
	}


	float sumweights = 0.0f;
	for(auto &i : childs)
		sumweights += i.weight;


	float PointF::* first, PointF::* second;
	if(type == horizontal)
	{
		first = &PointF::x;
		second = &PointF::y;
	}
	else
	{
		first = &PointF::y;
		second = &PointF::x;
	}


	count = 0;
	PointF off = refp;
	for(auto &i : childs)
	{
		i.layout->refp = off;
		i.layout->size.*first = size.*first * i.weight / sumweights;
		i.layout->size.*second = size.*second;
		i.layout->adjust();
		count += i.layout->count;
		off.*first += i.layout->size.*first;
	}

	return;
}

void Layout::free()
{
	for(auto &l : childs)
	{
		l.layout->free();
		delete l.layout;
	}
	childs.clear();
	return;
}



// find
Layout::Place Layout::place(int i)
{
	if(childs.empty() || mode == localmode)
		return { this, i };

	for(auto l : childs)
	{
		if(i < l.layout->count)
			return { l.layout, i };
		i -= l.layout->count;
	}
	throw std::out_of_range("Layout::place(): out of range");
}

Layout::PlaceConst Layout::place(int i) const
{
	if(childs.empty() || mode == localmode)
		return { this, i };

	for(auto l : childs)
	{
		if(i < l.layout->count)
			return { l.layout, i };
		i -= l.layout->count;
	}
	throw std::out_of_range("Layout::place(): out of range");
}





}





// end
