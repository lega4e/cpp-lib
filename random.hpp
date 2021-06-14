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
using uidis_t = std::uniform_int_distribution<T>;

template<typename T>
using urdis_t = std::uniform_real_distribution<T>;

typedef uidis_t<int>       uidisI, disI;
typedef uidis_t<long long> uidisLL, disLL;
typedef urdis_t<float>     urdisF, disF;
typedef urdis_t<double>    urdisD, disD;

/*
 * Почему-то первое значение, генерируемое dre
 * всегда одно и то же независимо от семени
 */
inline dre_t create_dre()
{
	dre_t dre(time(0));
	dre();
	return dre;
}





}

extern nvx::dre_t dre;





#endif
