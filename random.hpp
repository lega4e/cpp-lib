#ifndef NVX_RANDOM_HPP
#define NVX_RANDOM_HPP

/*
 * Этот файл содержит псевдонимы типов для получения
 * псевдослучайных чисел
 */

#include <random>





namespace nvx
{
	




typedef std::default_random_engine dre_t;

template<typename T>
using uidis_type = std::uniform_int_distribution<T>;

template<typename T>
using urdis_type = std::uniform_real_distribution<T>;

typedef uidis_type<int> uidisI, disI;
typedef uidis_type<long long> uidisLL, disLL;
typedef urdis_type<float> urdisF, disF;
typedef urdis_type<double> urdisD, disD;






}

extern nvx::dre_t dre;





#endif
