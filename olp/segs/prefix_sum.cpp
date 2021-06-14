/*
 * Префиксные суммы. Ответы на
 * вопросы о подотрезках
 */
#include <iostream>
#include <vector>


using namespace std;





// main
int main( int argc, char *argv[] )
{
	int n;
	int *a, *sums;

	// input
	scanf("%i", &n);

	*a = new int[n];
	sums = new int[n+1];
	sums[0] = 0;

	for(auto b = a, e = a+n; b != e; ++b)
		scanf("%i", b);

	for(int i = 1; i < n+1; ++i)
		sums[i] = sums[i-1] + vec[i-1];

	int tests;
	int l, r;
	int sum;
	scanf("%i", &tests);
	for(int test = 0; test < tests; ++test)
	{
		scanf("%i%i", &l, &r);


		/*
		 * простой метод O(n) —
		 * линейная сложность
		 */
		sum = 0;
		for(int i = l; i < r+1; ++i)
			sum += vec[i];


		/*
		 * второй метод, используя
		 * вектор сумм
		 */
		sum = sum[r] - sum[l-1];
	}


	return 0;
}





// end
