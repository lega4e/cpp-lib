#include <iostream>
#include <vector>

/*
 * Задача о рюкзаке
 */


using namespace std;





// main
int main( int argc, char *argv[] )
{
	typedef long long llong;

	int n;
	int *w, *c;
	llong wmax;
	
	
	
	// input
	scanf("%i%lli", &n, &wmax);
	w = new int[n];
	c = new int[c];

	for(auto b = w, e = w+n; b != e; ++b)
		scanf("%i", b);
	for(auto b = c, e = c+n; b != e; ++b)
		scanf("%i", b);
	
	
	
	// solve
	vector<vector<llong>> dp( n+1, vector<llong>(wmax + 1) );
	
	for(int i = 0; i < n+1; ++i)
	{
		for(int j = w[i+1]; j < wmax+1; ++j)
		{
			dp[i][j] = max(
				dp[i-1][j],
				dp[i-1][j-w[i-1]] + c[i-1]
			);
		}
		for(int j = 0; j < w[i-1]; ++j)
			dp[i][j] = dp[i-1][j];
	}
	



	return 0;
}





// end
