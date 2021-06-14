#ifndef NVX_STOPWATCH_HPP
#define NVX_STOPWATCH_HPP

#include <chrono>





namespace nvx
{



/*
 * Использовать так:
 *
 * 1. Чтобы начать отсчёт, необходимо вызвать start()
 * 2. Чтобы получить время, прошедшее с начала отсчёта,
 *    необходимо 1) либо вызвать метод duration(); при этом
 *    часы продолжат идти; 2) либо сначала остановить часы
 *    методом pause(), после чего уже получить время методом
 *    duration(); чтобы продолжить ход часов, необходимо
 *    вновь вызвать start()
 * 3. Чтобы сбросить часы, вызовите reset() (часы останавли
 *    ваются при этом)
 * 4. Чтобы узнать, идут ли в данный момент часы, вызовите
 *    runing()
 * 5. Чтобы поставить секундомер на паузу вызвовите метод
 *    pause(), чтобы запустить снова, вызовите start()
 * 6. Вместо duration можно использовать функции
 *    milliseconds, seconds и проч. они возвращают соот-
 *    ветствующие значения
 */

template<typename Clock>
class Stopwatch
{
public:
	typedef Clock clock_type;
	typedef typename Clock::time_point time_point_type;
	typedef typename Clock::duration duration_type;



	Stopwatch &start()
	{
		if(runing_)
			return *this;
		starttime_ = clock_type::now();
		runing_ = true;
		return *this;
	}

	Stopwatch &pause()
	{
		if(!runing_)
			return *this;
		duration_ += clock_type::now() - starttime_;
		runing_ = false;
		return *this;
	}

	Stopwatch &reset()
	{
		duration_ = duration_type::zero();
		runing_ = false;
		return *this;
	}

	bool runing() const
	{
		return runing_;
	}



	duration_type const &duration() const
	{
		if(runing_)
		{
			time_point_type now = clock_type::now();
			duration_ += now - starttime_;
			starttime_ = now;
		}

		return duration_;
	}

	long long nanoseconds() const
	{
		return std::chrono::duration_cast<
			std::chrono::nanoseconds
		>( duration() ).count();
	}

	double microseconds() const
	{
		return std::chrono::duration_cast<
			std::chrono::duration< double, std::ratio<1, 1000000> >
		>( duration() ).count();
	}

	double milliseconds() const
	{
		return std::chrono::duration_cast<
			std::chrono::duration< double, std::ratio<1, 1000> >
		>( duration() ).count();
	}

	double seconds() const
	{
		return std::chrono::duration_cast<
			std::chrono::duration< double, std::ratio<1, 1> >
		>( duration() ).count();
	}

	double minutes() const
	{
		return std::chrono::duration_cast<
			std::chrono::duration< double, std::ratio<60, 1> >
		>( duration() ).count();
	}

	double hours() const
	{
		return std::chrono::duration_cast<
			std::chrono::duration< double, std::ratio<3600, 1> >
		>( duration() ).count();
	}



private:
	bool runing_ = false;

	mutable time_point_type starttime_ = clock_type::now();
	mutable duration_type duration_ = duration_type::zero();


};

typedef Stopwatch<std::chrono::system_clock> stopwatch_type, stopwatch_t;




}





#endif
