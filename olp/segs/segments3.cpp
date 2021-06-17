/*
 * Отрезки как события.
 * Найти длинну покрытия
 */
#include <algorithm>
#include <iostream>


using namespace std;





// types
/*
 * Отрезок
 */
typedef long long llong;

struct Segment
{
	llong l, r;
};

struct Event
{
	llong pos;
	char type; // 'b', 'e'
};





// main
int main( int argc, char *argv[] )
{

	int n;
	Segment *segs;
	Event *events;

	// input segs
	scanf("%i", &n);
	segs = new Segment[n];
	for(auto *b = segs, *e = segs+n; b != e; ++b)
		scanf("%i", &b->l),
		scanf("%i", &b->r);



	// prepare
	events = new Event[n*2];
	for(int i = 0; i < n; ++i)
	{
		events[i*2] = { segs[i].l, 'b' };
		events[i*2 + 1] = { segs[i].r, 'e' };
	}
	sort(events, events+2*n, [](Event lhs, Event rhs)->bool {
		if(lhs.pos != rhs.pos)
			return lhs.pos < rhs.pos;
		if(lhs.type == rhs.type)
			return true;
		return lhs.type == 'b';
	});



	// solve
	llong cur = 0;
	llong sum = 0;
	for(int i = 0; i < 2*n; ++i)
	{
		if(cur)
			sum += events[i] - events[i-1];

		if(events[i].type == 'b')
			++cur;
		else
			--cur;
	}



	// output
	printf("%i\n", res);



	return 0;
}





// end
