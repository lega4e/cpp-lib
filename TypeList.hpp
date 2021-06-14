#ifndef TYPE_LIST
#define TYPE_LIST

#include <nvx/meta.hpp>





namespace nvx
{





template<typename T, typename NAME, typename U = void>
struct TElement;

template<typename T, char...Chars, typename U>
struct TElement<T, nvx::String<Chars...>, U>
{
	typedef T type;
	typedef nvx::String<Chars...> name_type;
	typedef U atype; // additional type

	static constexpr char const *name = name_type::value;
};



template<typename...Args>
struct TypeList;

template<typename Head, typename...Args>
struct TypeList< Head, Args... >
{
	typedef Head head;
	typedef TypeList<Args...> next;
};

template<typename Head>
struct TypeList< Head >
{
	typedef Head head;
};




#define NVX_DEFINE_TYPE_LIST_FOREACH_FUNCTION(funname, contentfun, argtype) \
template<typename T, typename Name, typename U> \
void funname(nvx::TypeList< nvx::TElement<T, Name, U> >, argtype arg) \
{ \
	typedef nvx::TypeList< nvx::TElement<T, Name, U> > list; \
	contentfun< \
		typename list::head::type, \
		typename list::head::atype \
	>(list::head::name, arg); \
	return; \
} \
 \
template<typename T, typename...Args> \
void funname(nvx::TypeList< T, Args... >, argtype arg) \
{ \
	typedef nvx::TypeList< T, Args... > list; \
	contentfun< \
		typename list::head::type, \
		typename list::head::atype \
	>(list::head::name, arg); \
	funname(nvx::TypeList<Args...>(), arg); \
	return; \
}





}





#endif
