/*
 * Два указателя
 */
#include <algorithm>
#include <iostream>


using namespace std;





// main
int main( int argc, char *argv[] )
{
	int n;
	int *aval, *bval;
	int k;



	// input
	scanf("%i%i", &n, &k);
	aval = new int[n];
	bval = new int[n];

	for(auto b = aval, e = aval+n; b != e; ++b)
		scanf("%i", b);
	for(auto b = bval, e = bval+n; b != e; ++b)
		scanf("%i", b);



	// solve
	sort(aval, aval+n);
	sort(bval, bval+n);
	sum = 0;
	for(int l = 0, r = n; l < r && r > 0; ++l)
	{
		while(r != 0 && a[l]+b[r-1] >= k)
		{
			--r;
		}
		sum += r-l;
	}




	return 0;
}





// end
