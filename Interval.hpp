#ifndef NVX_INTERVAL_HPP
#define NVX_INTERVAL_HPP

#include <initializer_list>
#include <random>
#include <vector>





namespace nvx
{





/*
 * Структура представляет собой интервал, а также
 * содержит метод, который позволяет генерировать
 * псевдослучайное значение внутри этого интервала,
 * т.е. в интервале [min, max].
 *
 * Метод rand работает лишь тогда, когда value_type
 * является int, long long, float или double
 */
template<typename T>
struct Interval
{
	typedef T value_type;

	T min = T(), max = T();

	/*
	 * Сгенерировать случайное значение внутри
	 * интервала [min, max]
	 */
	T rand(std::default_random_engine &dre) const
	{
		return rand_(dre, T());
	}

	template<class Ostream>
	Ostream &print( Ostream &os ) const
	{
		os << "[" << min << ", " << max << "]";
		return os;
	}

private:
	int rand_(std::default_random_engine &dre, int) const
	{
		return std::uniform_int_distribution<int>(min, max)(dre);
	}

	long long rand(std::default_random_engine &dre, long long) const
	{
		return std::uniform_int_distribution<long long>(min, max)(dre);
	}


	float rand(std::default_random_engine &dre, float) const
	{
		return std::uniform_real_distribution<float>(min, max)(dre);
	}

	double rand(std::default_random_engine &dre, double) const
	{
		return std::uniform_real_distribution<double>(min, max)(dre);
	}
};

template<class Ostream, typename T>
inline Ostream &operator<<( Ostream &os, Interval<T> const &toprint )
{
	toprint.print(os);
	return os;
}

typedef Interval<int> IntervalI;
typedef Interval<long long> IntervalLL;
typedef Interval<float> IntervalF;
typedef Interval<double> IntervalD;





/*
 * Этот класс реализует распределение между элементами, у
 * которых есть вес; вес влияет на то, с какой вероятностью
 * будет попадаться тот или иной элемент
 *
 * Веса берутся из родительского класса — вектора; все веса
 * должны быть неотрицательны; если вес равен нулю, то элемнт
 * с данным номером никогда не будет возвращён методом rand
 *
 * По умолчанию каждый раз, когда генерируется новое случайное
 * значение, сумма всех весов считается заново; чтобы этого
 * избежать, необходимо вызвать метод calculate, однако после
 * этого веса не должны меняться (если всё-таки это необходимо
 * сделать, то после изменения весов снова вызовите метод
 * calculate); чтобы сумма весов считалась каждый раз,
 * вызывается метод reset_calculated
 */
template<typename T>
class WeightDistribution: std::vector<T>
{
	typedef T value_type;



	// create
	WeightDistribution() {}

	WeightDistribution(
		std::vector<value_type> const &vec
	): std::vector<T>(vec) {}

	WeightDistribution(
		std::vector<value_type> &&vec
	): std::vector<T>( std::move(vec) ) {}

	WeightDistribution(
		std::initializer_list<value_type> const &list
	): std::vector<T>( std::move(list) ) {}



	// methods
	/*
	 * Сгенерировать случайное значение от 0 до size()-1,
	 * вероятность каждого из которых зависит от весов
	 */
	int rand( std::default_random_engine &dre ) const
	{
		if(!calculated_)
		{
			sum = 0.0;
			for(
				auto
					b = std::vector<T>::begin(),
					e = std::vector<T>::end();
				b != e; ++b
			)
				sum += *b;
		}

		std::uniform_real_distribution<double> dis(0.0, sum);
		double choice = dis(dre);
		for(
			auto
				b = std::vector<T>::begin(),
				e = std::vector<T>::end();
			b != e; ++b
		)
		{
			if( fabs(*b) > 0.000001 && choice - *b < 0.000001 )
				return b - std::vector<T>::begin();
			choice -= *b;
		}

		fprintf(stderr, "Error in WeightDistribution::rand: choice out of sum of weights\n");
		exit(1);
	}

	/*
	 * Посчитать сумму всех весов
	 */
	void calculate() const
	{
		sum = 0.0;
		for(auto b = std::vector<T>::begin(), e = std::vector<T>::end(); b != e; ++b)
			sum += *b;
		calculated_ = true;
		return;
	}

	/*
	 * Если веса изменились и теперь нужно, чтобы сумма
	 * всех весов считалась каждый раз при генерировании
	 * нового случайного значения
	 */
	void reset_calculated() const
	{
		calculated_ = false;
		return;
	}



private:
	mutable bool calculated_ = false;
	mutable double sum;



};





}





#endif
