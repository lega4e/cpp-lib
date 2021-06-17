/*
 * Отрезки как события
 */
#include <iostream>


using namespace std;





// types
/*
 * Отрезок
 */
struct Segment
{
	int l, r;
};





// functions
/*
 * сколько отрезков покрывают
 * данную точку
 */
int solve(int pos, Segment const *segs, int n)
{
	int res = 0;
	for(auto *b = segs, *e = segs+n; b != e; ++b)
	{
		if( b->l <= res && res <= b->r )
			++res;
	}
	return res;
}





// main
int main( int argc, char *argv[] )
{

	int n;
	Segment *segs;

	// input segs
	// ...



	// solve




	return 0;
}





// end
