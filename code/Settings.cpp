#include <nvx/Settings.hpp>





namespace nvx
{





/*
 * core
 */
Settings::Settings(adjfun_type adjfun): _adjfun(adjfun) {}

Settings::Settings(container_type const &cont, adjfun_type adjfun):
	_values(cont), _adjfun(adjfun) {}

Settings::~Settings() {}


void Settings::adjust() const
{
	if(_adjfun)
		_adjfun(*this);
	return;
}



/*
 * set
 */
/*
 * Settings &Settings::set(std::string const &name, std::any obj)
 * {
 *     _values[name] = obj;
 *     return *this;
 * }
 */



/*
 * adjust function
 */
Settings &Settings::adjustFunction(adjfun_type adjfun)
{
	_adjfun = adjfun;
	return *this;
}

Settings::adjfun_type Settings::adjustFunction() const
{
	return _adjfun;
}





}





// end
