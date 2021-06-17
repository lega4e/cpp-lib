#include <iostream>
#include <fstream>

#include <nvx/olp/geometry.cpp>


using namespace std;





// main
int main( int argc, char *argv[] )
{
	Point a, b, c, p;
	cin >>
		a.x >> a.y >>
		b.x >> b.y >>
		c.x >> c.y >>
		p.x >> p.y;

	if( belong(p, a, b, c) )
		cout << "In" << endl;
	else
		cout << "Out" << endl;


	return 0;
}





// end
