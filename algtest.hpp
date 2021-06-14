#ifndef NVX_ALGTEST_HPP_8736781987
#define NVX_ALGTEST_HPP_8736781987

#include <algorithm>
#include <chrono>
#include <ctime>
#include <numeric>
#include <vector>

#include <nvx/Stopwatch.hpp>
#include <nvx/random.hpp>





namespace nvx
{





// types
struct ArrayDataGenerator
{
	std::vector<int> arr;

	inline void set(int iteration)
	{
		arr.resize(iteration);
		std::iota( arr.begin(), arr.end(), 0 );
	}

	inline std::vector<int> &operator()()
	{
		std::shuffle( arr.begin(), arr.end(), dre );
		return arr;
	}

	dre_type dre = dre_type(time(0));
};


llong fib(int n);

struct GcdDataGenerator
{
	int c;

	inline void set(int c)
	{
		this->c = c;
		return;
	}

	inline std::pair<llong, llong> operator()() const
	{
		return make_pair( fib(c), fib(c+1) );
	}
};





// functions
/*
 * На вход подаётся:
 *   1. alg — сам алгоритм, который тестируется,
 *      должен быть вызываемым объектом с
 *      operator()(decltype(gen()))
 *   2. gen — генератор данных, долежн реализовывать
 *      методы operator()(), который возвращает
 *      данные для алгоритма, и set(int), куда
 *      передаётся номер итерации
 *   3-4. min, max — границы итераций (включительно)
 *   5. repeatc количество повторений на каждой
 *      итерации
 *
 * Функция возвращает вектор точек: номер итерации/
 * время в микросекундах
 */
template<typename Algorithm, typename DataGenerator>
std::vector<std::pair<int, double>> testing( 
	Algorithm alg, DataGenerator gen,
	int min, int max, int repeatc
)
{
	std::vector<std::pair<int, double>> result;
	stopwatch_type watch;

	double time;
	for(int i = min; i <= max; ++i)
	{
		gen.set(i);
		time = 0.0;
		for(int j = 0; j < repeatc; ++j)
		{
			auto data = gen();
			watch.reset().start();
			alg(data);
			watch.pause();
			time += watch.microseconds();
		}

		result.push_back( { i, time } );
	}

	return result;
}



/*
 * Самое большое — 91, дальше переполнение
 */
llong fib(int n)
{
	static vector<llong> numbers = { 1, 1 };

	if(n < (int)numbers.size())
		return numbers[n];

	llong a = fib(n-1), b = fib(n-2);
	numbers.push_back(a+b);

	return numbers[n];
}





}





#endif // NVX_ALGTEST_HPP_8736781987
