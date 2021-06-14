#include <nvx/string.hpp>

#include <algorithm>
#include <cstdarg>
#include <sstream>
#include <vector>


using namespace std;





namespace nvx
{





// FILLS
int count_symbols(std::string const &s)
{
	int syms = 0;
	for(int i = 0, bytes; i < (int)s.size(); ++i, ++syms)
	{
		bytes = 
			!(s[i] & (1 << 7)) ? 1 :
			!(s[i] & (1 << 5)) ? 2 :
			!(s[i] & (1 << 4)) ? 3 : 4;
		for(int j = 0; j < bytes-1; ++j)
			++i;
	}
	return syms;
}

void fills(std::string *s, int n)
{
	int syms = count_symbols(*s);
	if(n - syms <= 0)
		return;
	s->reserve( s->size() + (n - syms) );
	std::fill_n( std::back_inserter(*s), n - syms, ' ' );
	return;
}

std::string fills(std::string const &s, int n)
{
	int syms = count_symbols(s);
	if(n - syms <= 0)
		return s;
	std::string cp = s;
	cp.reserve( cp.size() + (n - syms) );
	std::fill_n( std::back_inserter(cp), n - syms, ' ' );
	return cp;
}

std::string fills(std::string &&s, int n)
{
	int syms = count_symbols(s);
	if(n - syms <= 0)
		return s;
	s.reserve(s.size() + (n - syms));
	std::fill_n( std::back_inserter(s), n - syms, ' ' );
	return s;
}





// OTHER
void genkeys(
	vector<string> const &names,
	vector<string> &keys,
	bool letcase
)
{
	keys.resize(names.size());

	for(int i = 0; i < (int)names.size(); ++i)
	{
		if(!keys[i].empty())
			continue;

		for(auto b = names[i].begin(), e = names[i].end(); b != e; ++b)
		{
			if( find_if(
				keys.begin(), keys.end(),
				[b, letcase](string const &s)->bool {
					return !s.empty() &&
						(letcase ? *b : tolower(*b)) ==
						s.front();
				}
			) == keys.end() )
			{
				keys[i].push_back(
					letcase ? *b : tolower(*b)
				);
				break;
			}
		}
	}

	return;
}



string format(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vector<char> v(64);
	
	while (true)
	{	
		va_list args2;
		va_copy(args2, args);
		int res = vsnprintf(v.data(), v.size(), fmt, args2);

		if( res >= 0 && res < (int)v.size() )
		{
			va_end(args);
			va_end(args2);
			return std::string(v.data());
		}

		v.clear();
		v.resize( res < 0 ? v.size()*2 : res+1 );
		va_end(args2);
	}
}



bool scan(
	string const &enter,
	char const *fmt,
	void **dat
)
{
	stringstream ss(enter);

	for(char const *ch = fmt; *ch != '\0'; ++ch, ++dat)
	{
		switch(*ch)
		{
		case 'c':
			ss >> *(char *)*dat;
			break;

		case 'i':
			ss >> *(int *)*dat;
			break;

		case 'l':
			ss >> *(long *)*dat;
			break;

		case 'u':
			ss >> *(unsigned int *)*dat;
			break;

		case 'f':
			ss >> *(float *)*dat;
			break;

		case 'd':
			ss >> *(double *)*dat;
			break;

		case 's': case 'w':
			ss >> *(string *)*dat;
			if( ((string *)*dat)->empty() )
				return false;
			break;

		case 'a':
			{
				string &str = *(string *)*dat;
				while(ss)
					str.push_back(ss.get());
				str.pop_back();
				cutspace(str);
				if(str.empty())
					return false;
			}
			return true;

		default:
			throw logic_error("Form::getarg -> unknown type");
		}
		if(ss.fail())
			return false;
	}

	return true;
}





}





// end
