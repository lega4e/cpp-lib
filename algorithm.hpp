#ifndef NVX_ALGORITHM_HPP_38298320
#define NVX_ALGORITHM_HPP_38298320

#include <type_traits>





namespace nvx
{





template<typename T, typename IteratorType>
void summation(IteratorType b, IteratorType e, T &accum)
{
	while(b != e)
	{
		accum += *b;
		++b;
	}
	return;
}

template<typename T, typename IteratorType>
auto summation(IteratorType b, IteratorType e)
{
	decltype(*b) accum = decltype(*b)();
	while(b != e)
	{
		accum += *b;
		++b;
	}
	return accum;
}

template<typename IteratorType, typename AccumFunctor>
auto accumulate(IteratorType b, IteratorType e, AccumFunctor f)
{
	auto accum = typename std::remove_reference<decltype(*b)>::type();
	while(b != e)
	{
		accum = f(accum, *b);
		++b;
	}
	return accum;
}





}





#endif // NVX_ALGORITHM_HPP
