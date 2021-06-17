#ifndef NVX_FIELD_HPP
#define NVX_FIELD_HPP

#include <cstring>
#include <iterator>
#include <type_traits>
#include <utility>

#include <nvx/iostream.hpp>
#include <nvx/meta.hpp>
#include <nvx/math.hpp>
#include <nvx/point.hpp>





namespace nvx
{





template<typename ValueType>
struct Field
{
	// types
	typedef ValueType value_type;



		// iterator-class
private:
	struct Simple {};
	struct Const {};
	struct TapeAt {};

	template<class IsConst, class TapeMode>
	class Iterator: public std::iterator<
		std::bidirectional_iterator_tag,
		typename IF<
			std::is_same<IsConst, Const>::value,
			Field::value_type const,
			Field::value_type
		>::type
	>
	{
	public:
		// types
		typedef typename Iterator::value_type value_type;

		typedef typename IF<
			std::is_same<IsConst, Const>::value,
			Field const, Field
		>::type field_type;





		// copy
		template<class C, class TM>
		Iterator( Iterator<C, TM> const &tocp );

		template<class C, class TM>
		Iterator &operator=(Iterator<C, TM> const &rhs);



		// move
		Iterator &operator++();
		inline Iterator operator++(int);

		Iterator &operator--();
		inline Iterator operator--(int);

		Iterator &incy();
		Iterator &incy(int n);

		Iterator &reducey();
		Iterator &reducey(int n);




		// at
		inline value_type &operator*() const;
		inline value_type *operator->() const;

		inline value_type *base() const;
		inline PointI point() const;



		// get info
		template<class C, class TM>
		bool operator==(Iterator<C, TM> const &rhs) const;

		template<class C, class TM>
		inline bool operator!=(Iterator<C, TM> const &rhs) const;

		inline bool isedge() const;
		inline bool isend() const;

		// создаёт новый итератор, который можно потом изменять:
		// отправить, например, в функцию make_reverse_iterator;
		// из этого итератора может выйти. Но создаётся новый! В
		// цикле вызывать эту функцию для проверки дошёл ли до
		// конца итератор - нельзя, используй для этого либо isend,
		// либо iterendc
		Iterator iterend() const;
		static inline Iterator const &citerend();



	private:
		friend class Field;

		static Iterator create_iterend();



		// methods
		Iterator();
		Iterator(
			field_type &field,
			int left = 0, int top = 0,
			int width = -1, int height = -1
		);

		inline void plusplus(Simple);
		inline void plusplus(TapeAt);

		inline void minusminus(Simple);
		inline void minusminus(TapeAt);



		// data-members
		int top, left, width, height, fw, fh;
		int x, y;
		value_type *d, *fd;




	};



public:
		// other
	typedef Iterator<Simple, Simple> iterator_type;
	typedef Iterator<Const, Simple> const_iterator_type;
	typedef Iterator<Simple, TapeAt> iterator_tape_type;
	typedef Iterator<Const, TapeAt> const_iterator_tape_type;





	// static const members
	static constexpr int const OFFSET_COUNT = 8;
	static constexpr int const OFFSET[OFFSET_COUNT][2] = {
		{ -1, -1 }, { 0, -1 }, { 1, -1 }, //  Directions:
		                       { 1, 0  }, //  0  1  2
		                       { 1, 1  }, //  7  *  3
		            { 0, 1  },            //  6  5  4
		{ -1, 1  },                       //
		{ -1, 0  },                       //
	};





	// data-members
	int w = 0, h = 0;
	value_type *d = nullptr;





	// init, free
	inline Field &init();
	inline Field &init(int width, int height);
	inline Field &free();



	// clear & zeroize
	inline Field &clear();
	inline Field &clear(value_type const &value);

	inline Field &clearline(int line);
	inline Field &clearline(
		value_type const &value, int line
	);

	inline Field &clearlines(
		int bline, int nline
	);
	inline Field &clearlines(
		value_type const &value,
		int bline, int nline
	);

	inline Field &zeroize();
	inline Field &zeroize(int line);
	inline Field &zeroize(int bline, int nline);





	// check vlaid
		// simple
	inline bool isValid(int x, int y) const;

	template<class Point>
	inline bool isValid(Point const &p) const;



		// for near
	inline bool isValid(int x, int y, int dir) const;

	template<class Point>
	inline bool isValid(Point const &p, int dir) const;





	// correct
	inline void correct(int &x, int &y) const;

	template<class Point>
	inline void correct(Point &p) const;





	// get
	inline void getxy(int i, int &x, int &y) const;
	inline PointI getxy(int i) const;

	inline void getxy(value_type const *p, int &x, int &y) const;
	inline PointI getxy(value_type const *p) const;

	inline int geti(int x, int y) const;

	template<class Point>
	inline int geti(Point const &p) const;



	// geometry
	inline PointF origin(int x, int y, float a) const;
	inline PointF origin(PointI const &p, float a) const;
	inline PointF origin(value_type const *p, float a) const;





	// at
		// simple
	inline value_type &at(int x, int y);
	inline value_type const &at(int x, int y) const;


		// for point
	template<class Point>
	inline value_type const &at(
		Point const &p
	) const;

	template<class Point>
	inline value_type &at(
		Point const &p
	);



		// tape at simple
	inline value_type &att(int x, int y);
	inline value_type const &att(int x, int y) const;


		// tape at for point
	template<class Point>
	inline value_type const &att(
		Point const &p
	) const;

	template<class Point>
	inline value_type &att(
		Point const &p
	);



		// near at simple
	inline value_type &near(int x, int y, int dir);
	inline value_type const &near(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &near(Point const &p, int dir);

	template<class Point>
	inline value_type const &near(
		Point const &p, int dir
	) const;



		// near tape at simple
	inline value_type &neart(int x, int y, int dir);
	inline value_type const &neart(int x, int y, int dir) const;


		// near at for point
	template<class Point>
	inline value_type &neart(Point const &p, int dir);

	template<class Point>
	inline value_type const &neart(
		Point const &p, int dir
	) const;



		// operator at
	inline value_type const *operator[](char y) const;
	inline value_type *operator[](char y);

	inline value_type const *operator[](int y) const;
	inline value_type *operator[](int y);

	inline value_type const *operator[](long y) const;
	inline value_type *operator[](long y);

	inline value_type const *operator[](long long y) const;
	inline value_type *operator[](long long y);

	template<class Point>
	inline value_type const &operator[](Point const &p) const;

	template<class Point>
	inline value_type &operator[](Point const &p);





	// iterators
		// simple
	inline value_type *begin();
	inline value_type *end();

	inline value_type const *begin() const;
	inline value_type const *end() const;



		// for line
	inline value_type *begin(int line);
	inline value_type *end(int line);

	inline value_type const *begin(int line) const;
	inline value_type const *end(int line) const;



		// class-iterator
			// simple
	inline iterator_type iterator(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	);
	inline iterator_type const &iterend() const;

			// simple const
	inline const_iterator_type citerator(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	) const;
	inline const_iterator_type const &citerend() const;


			// tape
	inline iterator_tape_type iteratort(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	);
	inline iterator_tape_type const &iterendt() const;

			// tape const
	inline const_iterator_tape_type citeratort(
		int left = 0, int top = 0,
		int width = -1, int height = -1
	) const;
	inline const_iterator_tape_type const &citerendt() const;





	template<class Ostream>
	Ostream &print(
		Ostream &os,
		std::string const &elterm = "\t",
		std::string const &lnterm = "\n"
	) const;





};





// init, free;
template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::init()
{
	d = new value_type[w*h];
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::init(
	int neww, int newh
)
{
	w = neww; h = newh;
	d = new value_type[w*h];
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::free()
{
	delete[] d;
	return *this;
}





// clear & zeroize
template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::clear()
{
	clear(value_type());
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::clear(
	value_type const &value
)
{
	std::fill( begin(), end(), value );
	return *this;
}



template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::zeroize()
{
	memset(d, 0, sizeof(value_type)*w*h);
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::zeroize(int line)
{
	memset(d+line*w, 0, sizeof(value_type)*w);
	return *this;
}


template<typename ValueType>
inline Field<ValueType> &Field<ValueType>::zeroize(
	int bline, int nline
)
{
	memset(d+bline*w, 0, sizeof(value_type)*w*nline);
	return *this;
}







// check vlaid
	// simple
template<typename ValueType>
inline bool Field<ValueType>::isValid(int x, int y) const
{
	return x >= 0 && x < w && y >= 0 && y < h;
}


template<typename ValueType> template<class Point>
inline bool Field<ValueType>::isValid(
	Point const &p
) const
{
	return p.x >= 0 && p.x < w && p.y >= 0 && p.y < h;
}



	// for near
template<typename ValueType>
inline bool Field<ValueType>::isValid(
	int x, int y, int dir
) const
{
	return isValid(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}

template<typename ValueType> template<class Point>
inline bool Field<ValueType>::isValid(
	Point const &p, int dir
) const
{
	return isValid(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}





// correct
template<typename ValueType>
inline void Field<ValueType>::correct(int &x, int &y) const
{
	x = x < 0 ?
		w-1 - (-x-1)%w :
		x % w;
	y = y < 0 ?
		h-1 - (-y-1)%h :
		y % h;
	return;
}

template<typename ValueType> template<class Point>
inline void Field<ValueType>::correct(Point &p) const
{
	p.x = p.x < 0 ?
		( int(p.x)%w == 0 ? 0 : int(p.x) - (int(p.x)/w - 1)*w ) :
		int(p.x) % w;
	p.y = p.y < 0 ?
		( int(p.y)%h == 0 ? 0 : int(p.y) - (int(p.y)/h - 1)*h ) :
		int(p.y) % h;
	return;
}





// get
template<typename ValueType>
inline void Field<ValueType>::getxy(
	int i, int &x, int &y
) const
{
	x = i%w;
	y = i/w;
	return;
}

template<typename ValueType>
inline PointI Field<ValueType>::getxy(
	int i
) const
{
	return { i%w, i/w };
}



template<typename ValueType>
inline void Field<ValueType>::getxy(
	typename Field<ValueType>::value_type const *p,
	int &x, int &y
) const
{
	x = (p-d)%w;
	y = (p-d)/w;
	return;
}

template<typename ValueType>
inline PointI Field<ValueType>::getxy(
	value_type const *p
) const
{
	return { (p-d) % w, (p-d) / w };
}



template<typename ValueType>
inline int Field<ValueType>::geti(
	int x, int y
) const
{
	return x + y*w;
}

template<typename ValueType> template<class Point>
inline int Field<ValueType>::geti(
	Point const &p
) const
{
	return p.x + p.y*w;
}







// geometry
template<typename ValueType>
inline PointF Field<ValueType>::origin(
	int x, int y, float a
) const
{
	return { x*a, y*a };
}

template<typename ValueType>
inline PointF Field<ValueType>::origin(
	PointI const &p, float a
) const
{
	return { p.x*a, p.y*a };
}

template<typename ValueType>
inline PointF Field<ValueType>::origin(
	value_type const *p, float a
) const
{
	return { (p-d)%w*a, (p-d)/w*a };
}







// at
	// simple
template<typename ValueType>
inline typename Field<ValueType>::value_type &
Field<ValueType>::at(int x, int y)
{
	return d[y*w+x];
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::at(int x, int y) const
{
	return d[y*w+x];
}



	// for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::at(Point const &p) const
{
	return d[p.y*w+p.x];
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type &
Field<ValueType>::at(
	Point const &p
)
{
	return d[p.y*w+p.x];
}





	// tape at simple
template<typename ValueType>
inline typename Field<ValueType>::value_type &
Field<ValueType>::att(int x, int y)
{
	correct(x, y);
	return d[y*w+x];
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::att(int x, int y) const
{
	correct(x, y);
	return d[y*w+x];
}



	// tape at for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::att(
	Point const &p
) const
{
	return att(p.x, p.y);
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type &
Field<ValueType>::att(
	Point const &p
)
{
	return att(p.x, p.y);
}



	// near at simple
template<typename ValueType>
inline typename Field<ValueType>::value_type
&Field<ValueType>::near(
	int x, int y, int dir
)
{
	return at( x + OFFSET[dir][0], y + OFFSET[dir][1] );
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::near(
	int x, int y, int dir
) const
{
	return at( x + OFFSET[dir][0], y + OFFSET[dir][1] );
}



	// near at for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type
&Field<ValueType>::near(
	Point const &p, int dir
)
{
	return at( p.x + OFFSET[dir][0], p.y + OFFSET[dir][1] );
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::near(
	Point const &p, int dir
) const
{
	return at( p.x + OFFSET[dir][0], p.y + OFFSET[dir][1] );
}





	// near tape at simple
template<typename ValueType>
inline typename Field<ValueType>::value_type
&Field<ValueType>::neart(
	int x, int y, int dir
)
{
	return att(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}

template<typename ValueType>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::neart(
	int x, int y, int dir
) const
{
	return att(
		x + OFFSET[dir][0],
		y + OFFSET[dir][1]
	);
}



	// near at for point
template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type
&Field<ValueType>::neart(
	Point const &p, int dir
)
{
	return att(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}

template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const
&Field<ValueType>::neart(
	Point const &p, int dir
) const
{
	return att(
		p.x + OFFSET[dir][0],
		p.y + OFFSET[dir][1]
	);
}





	// operator at
template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::operator[](char n) const
{
	return d + n*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::operator[](char n)
{
	return d + n*w;
}




template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::operator[](int n) const
{
	return d + n*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::operator[](int n)
{
	return d + n*w;
}




template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::operator[](long n) const
{
	return d + n*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::operator[](long n)
{
	return d + n*w;
}




template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::operator[](long long n) const
{
	return d + n*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::operator[](long long n)
{
	return d + n*w;
}




template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type const &
Field<ValueType>::operator[](Point const &p) const
{
	return at(p);
}


template<typename ValueType> template<class Point>
inline typename Field<ValueType>::value_type &
Field<ValueType>::operator[](Point const &p)
{
	return at(p);
}







// iterators
	// simple
template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::begin()
{
	return d;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::end()
{
	return d + w*h;
}



	// simple const
template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::begin() const
{
	return d;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::end() const
{
	return d + w*h;
}





	// for line
template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::begin(int line)
{
	return d + line*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type *
Field<ValueType>::end(int line)
{
	return d + (line+1)*w;
}



	// for line const
template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::begin(int line) const
{
	return d + line*w;
}


template<typename ValueType>
inline typename Field<ValueType>::value_type const *
Field<ValueType>::end(int line) const
{
	return d + (line+1)*w;
}





	// class-iterator
		// simple
template<typename ValueType>
inline typename Field<ValueType>::iterator_type
Field<ValueType>::iterator(
	int left, int top,
	int width, int height
)
{
	return iterator_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename Field<ValueType>::iterator_type const &
Field<ValueType>::iterend() const
{
	return iterator_type::citerend();
}


		// simple const
template<typename ValueType>
inline typename Field<ValueType>::const_iterator_type
Field<ValueType>::citerator(
	int left, int top,
	int width, int height
) const
{
	return const_iterator_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename Field<ValueType>::const_iterator_type const &
Field<ValueType>::citerend() const
{
	return const_iterator_type::citerend();
}



		// tape
template<typename ValueType>
inline typename Field<ValueType>::iterator_tape_type
Field<ValueType>::iteratort(
	int left, int top,
	int width, int height
)
{
	return iterator_tape_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename Field<ValueType>::iterator_tape_type const &
Field<ValueType>::iterendt() const
{
	return iterator_tape_type::enditer();
}


		// tape const
template<typename ValueType>
inline typename Field<ValueType>::const_iterator_tape_type
Field<ValueType>::citeratort(
	int left, int top,
	int width, int height
) const
{
	return const_iterator_tape_type(
		*this,
		left, top,
		width, height
	);
}

template<typename ValueType>
inline typename Field<ValueType>::const_iterator_tape_type const &
Field<ValueType>::citerendt() const
{
	return const_iterator_tape_type::enditerc();
}





// print
template<typename ValueType> template<class Ostream>
Ostream &Field<ValueType>::print(
	Ostream &os,
	std::string const &elterm,
	std::string const &lnterm
) const
{
	for(int y = 0; y < h; ++y)
	{
		for(int x = 0; x < w; ++x)
		{
			nvx::print(os, at(x, y)) << elterm;
		}
		os << lnterm;
	}
	return os;
}







// iterator-class
// copy
template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
Field<ValueType>::Iterator<IsConst, TapeMode>::Iterator(
	Iterator<C, TM> const &tocp
):
	left(tocp.left), top(tocp.top),
	width(tocp.width), height(tocp.height),
	fw(tocp.fw), fh(tocp.fh),
	x(tocp.x), y(tocp.y),
	d(tocp.d), fd(tocp.fd) {}

/*
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * template<class C, class TM>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::operator=(
 *     Iterator<C, TM> const &rhs
 * )
 * {
 *     left = rhs.left;
 *     top = rhs.top;
 *     width = rhs.width;
 *     height = rhs.height;
 *     fw = rhs.fw;
 *     fh = rhs.fh;
 *     x = rhs.x;
 *     y = rhs.y;
 *     d = rhs.d;
 *     fd = rhs.fd;
 *     return *this;
 * }
 *
 *
 *
 *
 *
 * // move
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::operator++()
 * {
 *     plusplus(TapeMode());
 *     return *this;
 * }
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>::operator++(int)
 * {
 *     auto athis = *this;
 *     operator++();
 *     return athis;
 * }
 *
 *
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::operator--()
 * {
 *
 *     minusminus(TapeMode());
 *     return *this;
 * }
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * inline Field<ValueType>::Iterator<IsConst, TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>::operator--(int)
 * {
 *     auto cp = *this;
 *     operator--();
 *     return cp;
 * }
 *
 *
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::incy()
 * {
 *     ++y;
 *     d += fw;
 *     return *this;
 * }
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::incy(int n)
 * {
 *     y += n;
 *     d += fw*n;
 *     return *this;
 * }
 *
 *
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::reducey()
 * {
 *     --y;
 *     d -= fw;
 *     return *this;
 * }
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::reducey(int n)
 * {
 *     y -= n;
 *     d -= fw*n;
 *     return *this;
 * }
 */





// at
template<typename ValueType>
template<class IsConst, class TapeMode>
typename Field<ValueType>::template Iterator<IsConst, TapeMode>::value_type &
Field<ValueType>::Iterator<IsConst, TapeMode>::operator*() const
{
	return *d;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
typename Field<ValueType>::template Iterator<IsConst, TapeMode>::value_type *
Field<ValueType>::Iterator<IsConst, TapeMode>::operator->() const
{
	return d;
}



template<typename ValueType>
template<class IsConst, class TapeMode>
inline typename Field<ValueType>::template Iterator<IsConst, TapeMode>::value_type *
Field<ValueType>::Iterator<IsConst, TapeMode>::base() const
{
	return d;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline PointI Field<ValueType>::Iterator<IsConst, TapeMode>::point() const
{
	return { x, y };
}





// get info
	// compare
template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
bool Field<ValueType>::Iterator<IsConst, TapeMode>::operator==(
	Field<ValueType>::Iterator<C, TM> const &rhs
) const
{
	if(d)
		return rhs.d ?
			x == rhs.x && y == rhs.y :
			isend();
	return rhs.d ?
		rhs.isend() :
		true;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
template<class C, class TM>
inline bool Field<ValueType>::Iterator<IsConst, TapeMode>::operator!=(
	Field<ValueType>::Iterator<C, TM> const &rhs
) const
{
	return !operator==(rhs);
}



	// end
template<typename ValueType>
template<class IsConst, class TapeMode>
inline bool Field<ValueType>::Iterator<IsConst, TapeMode>::isedge() const
{
	return x == left || x == left+width-1 || y == top || y == top+height-1;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline bool Field<ValueType>::Iterator<IsConst, TapeMode>::isend() const
{
	return y == height+top;
}

/*
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>::iterend() const
 * {
 *     auto e = *this;
 *     e.x = left;
 *     e.y = top+height;
 *     return e;
 * }
 *
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode> const &
 * Field<ValueType>::Iterator<IsConst, TapeMode>::citerend()
 * {
 *     static Iterator const singleton = create_iterend();
 *     return singleton;
 * }
 *
 *
 *
 *
 *
 *
 *
 * // private
 *     // static
 * template<typename ValueType>
 * template<class IsConst, class TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>
 * Field<ValueType>::Iterator<IsConst, TapeMode>::create_iterend()
 * {
 *     Iterator iter;
 *     iter.d = nullptr;
 *     return iter;
 * }
 */





	// constructor
template<typename ValueType>
template<class IsConst, class TapeMode>
Field<ValueType>::template Iterator<IsConst, TapeMode>::Iterator(): d(nullptr) {}

template<typename ValueType>
template<class IsConst, class TapeMode>
Field<ValueType>::template Iterator<IsConst, TapeMode>::Iterator(
	field_type &field,
	int left, int top,
	int width, int height
):
	left(left), top(top),
	width( width < 0 ? field.w-left : width ),
	height( height < 0 ? field.h-top : height ),
	fw(field.w), fh(field.h),
	x(left), y(top),
	d( &field.att(left, top) ), fd(field.d) {}



	// move
template<typename ValueType>
template<class IsConst, class TapeMode>
inline void Field<ValueType>::Iterator<IsConst, TapeMode>::plusplus(Simple)
{
	if(++x == width+left)
	{
		x = left;
		++y;
		d += fw-width+1;
	}
	else
		++d;
	return;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline void Field<ValueType>::Iterator<IsConst, TapeMode>::plusplus(TapeAt)
{
	if(++x == width+left)
	{
		x = left;
		++y;
	}
	d = fd + mod(x, fw) + mod(y, fh)*fw;

	return;
}



template<typename ValueType>
template<class IsConst, class TapeMode>
inline void Field<ValueType>::Iterator<IsConst, TapeMode>::minusminus(Simple)
{
	if(--x == left-1)
	{
		x = left+width-1;
		--y;
	}
	d = fd + x + y*fw;

	return;
}

template<typename ValueType>
template<class IsConst, class TapeMode>
inline void Field<ValueType>::Iterator<IsConst, TapeMode>::minusminus(TapeAt)
{
	if(--x == left-1)
	{
		x = left+width-1;
		--y;
	}
	d = fd + mod(x, fw) + mod(y, fh)*fw;

	return;
}







// end





}





template<class Ostream, typename ValueType>
Ostream &operator<<(Ostream &os, nvx::Field<ValueType> const &toprint)
{
	toprint.print(os);
	return os;
}





#endif
