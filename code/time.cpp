#include <nvx/time.hpp>





namespace nvx
{





std::string ftime(char const *fmt, time_t time)
{
	if(time < 0)
		time = ::time(nullptr);

	struct tm const *info = localtime(&time);

	std::string s;
	s.resize(32);

	size_t sz;
again:
	sz = strftime((char *)s.data(), s.size(), fmt, info);
	if(!sz)
	{
		s.resize(s.size()*2);
		goto again;
	}

	s.resize( strlen(s.data()) );

	char stage = 0;
	std::string ret;
	for(int i = 0; i < (int)s.size(); ++i)
	{
		switch(stage)
		{
		case 0:
			if(s[i] == '$')
				stage = '$';
			else
				ret.push_back(s[i]);
			break;

		case '$':
			switch(s[i])
			{
			case 'm':
				ret += months_rus_lower[info->tm_mon];			
				break;
			case 'M':
				ret += months_rus[info->tm_mon];			
				break;
			case 'w':
				ret += weekdays_rus_lower[(info->tm_wday + 6) % 7];
				break;
			case 'W':
				ret += weekdays_rus[(info->tm_wday + 6) % 7];			
				break;
			default:
				ret.push_back('$');	
				if(s[i] != '$')
					ret.push_back(s[i]);
				break;
			}
			stage = 0;
			break;
		default:
			throw 381021;

		}
	}

	return ret;
}





}





// end
