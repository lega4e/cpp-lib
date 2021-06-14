#ifndef NVX_STRING_HPP
#define NVX_STRING_HPP

#include <sstream>
#include <string>
#include <vector>





namespace nvx
{





// CUT ZERO
inline std::string cutzero(std::string const &s)
{
	auto pos = s.find_last_not_of('0');
	if(pos == s.npos)
		return s;
	return s[pos] == '.' ?
		s.substr( 0, pos+2 ) :
		s.substr( 0, pos+1 );
}

inline void cutzero(std::string *s)
{
	auto pos = s->find_last_not_of('0');
	if(pos == s->npos)
		return;
	(*s)[pos] == '.' ?
		s->erase(pos+2) :
		s->erase(pos+1);
	return;
}




inline void cutspace(std::string *s)
{
	auto b = s->find_first_not_of(" \t\n");
	if(b == std::string::npos)
	{
		*s = "";
		return;
	}
	*s = s->substr(
		b, s->find_last_not_of(" \t\n") - b + 1
	);
	return;
}

inline std::string cutspace(std::string const &s)
{
	auto b = s.find_first_not_of(" \t\n");
	if(b == std::string::npos)
		return "";
	return s.substr(
		b, s.find_last_not_of(" \t\n") - b + 1
	);
}

inline std::vector<std::string> split(std::string const &s, char d)
{
	std::stringstream ss(s);
	std::string item;
	std::vector<std::string> res;

	while(std::getline(ss, item, d))
	{
		res.push_back(std::move(item));
	}

	return res;
}

template<typename Iterator>
std::string join(Iterator b, Iterator e, std::string const &between)
{
	if(b == e)
		return "";

	std::string res = *b;
	while(++b != e)
	{
		res += between;
		res += *b;
	}

	return res;
}





// FILLS
int count_symbols(std::string const &s);
void fills(std::string *s, int n);
std::string fills(std::string const &s, int n);
std::string fills(std::string &&s, int n);



inline void fills(std::wstring *s, int n)
{
	if((int)s->size() >= n)
		return;
	s->reserve(n);
	std::fill_n( std::back_inserter(*s), n-s->size(), L' ' );
	return;
}

inline std::wstring fills(std::wstring const &s, int n)
{
	if((int)s.size() >= n)
		return s;
	std::wstring cp = s;
	cp.reserve(n);
	std::fill_n( std::back_inserter(cp), n-cp.size(), L' ' );
	return cp;
}

inline std::wstring fills(std::wstring &&s, int n)
{
	if((int)s.size() >= n)
		return s;
	s.reserve(n);
	std::fill_n( std::back_inserter(s), n-s.size(), L' ' );
	return s;
}





// OTHER
void genkeys(
	std::vector<std::string> const &names,
	std::vector<std::string> &keys,
	bool letcase = false
);

std::string format(const char *fmt, ...);

template<typename T>
inline std::string operator%(std::string const &s, T const &t)
{
	return format(s.c_str(), t);
}



/*
 * Вычленяет объекты из строки
 *   i — int
 *   l - long
 *   u - unsigned int
 *   f - float
 *   d - double
 *   s,w - std::string
 *   a — кладёт всю оставшуюся строку в std::string
 *
 * тип вычленяемого объекта и их порядок получается из fmt;
 * fmt может выглядеть так: "iifs" — тогда сначала считается
 * int, затем ещё раз int, далее float и в конце std::string.
 * Всё это записывается в dat. Для вычленения используется
 * stringstream::operator>>(...)
 */
bool scan(
	std::string const &enter,
	char const *fmt,
	void **dat
);

inline bool scan(
	std::string const &enter,
	char const *fmt,
	std::vector<void *> dat
)
{
	return scan(enter, fmt, dat.data());
}





}





inline std::string operator*(int c, std::string const &s)
{
	std::string res;
	res.resize(s.size()*c);
	for(int i = 0; i < (int)res.size(); ++i)
		res[i] = s[i % s.size()];
	return res;
}

inline std::string operator*(std::string const &s, int c)
{
	return c*s;
}





#endif
