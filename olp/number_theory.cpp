#include <cmath>
#include <vector>

using namespace std;





// types
typedef long long llong;





// functions
/*
 * Алгоритм Евклида по нахождению НОД;
 * расширенный алгоритм Евклида, который находит
 * также корни диофантова уравнения
 * 	a*x + b*y = gcd(a, b);
 * с помощью расширенного алгоритма Евклида
 * можно найти обратный по простому модулю элемент,
 * нужный, чтобы делить под модулем (это будет x);
 * а также НОК
 */
llong gcd(llong a, llong b)
{
	while(a)
	{
		b %= a;
		swap(a, b);
	}
	return b;
}

llong exgcd(llong a, llong b, llong &x, llong &y)
{
	if(a == 0)
	{
		x = 0, y = 1;
		return b;
	}

	llong xx, yy, g;
	g = exgcd(b%a, a, xx, yy);
	x = yy - xx*(b/a);
	y = xx;
	return g;
}

inline llong lcm(llong a, llong b)
{
	return a/gcd(a, b)*b;
}



/*
 * Математический модуль числа;
 * разделить число под простым модулем
 */
inline llong mod(llong a, llong b)
{
	return (b + a%b) % b;
}

inline llong div(llong a, llong b, llong m)
{
	llong nul;
	exgcd(b, m, b, nul);
	return mod(a*b, m);
}



/*
 * Решето Эратосфена, которое находит все 
 * простые числа (они помечаются нулями),
 * меньшие n; а также по количеству простых
 * чисел (вычисляется всегда чуть больше)
 */
void sieve(llong n, vector<llong> &sie)
{
	sie.assign(n, 0);
	sie[0] = sie[1] = 1; // вычёркиваем 0 и 1
	for(llong i = 2; i*i < n; ++i)
	{
		if(sie[i])
			continue;
		for(llong j = i*i; j < n; j += i)
			sie[j] = i; // записываем первый делить числа
	}
}

void sieve_by_count(llong count, vector<llong> &sie)
{
	sieve(
		count * ceil(log(count)) * 6 / 5 + 5,
		sie
	);
	return;
}





// end
