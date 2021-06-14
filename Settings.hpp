#ifndef NVX_QT_SETTINGS_47834
#define NVX_QT_SETTINGS_47834

#include <any>
#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>





namespace nvx
{





class Settings
{
public:
	typedef std::function<void(Settings const &)> adjfun_type;
	typedef std::unordered_map<std::string, std::any> container_type;
	
	Settings(adjfun_type adjfun = adjfun_type());
	Settings(container_type const &cont, adjfun_type adjfun = adjfun_type());
	~Settings();

	void adjust() const;

	template<typename T>
	Settings &set(std::string const &name, T const &obj)
	{
		_values[name] = obj;
		return *this;
	}

	template<typename T>
	T const &get(std::string const &name) const
	{
		auto it = _values.find(name);
		if(it == _values.end())
			throw std::out_of_range("Can't find setting '" + name + "'");
		return std::any_cast<T const &>(it->second);
	}

	Settings &adjustFunction(adjfun_type adjfun);
	adjfun_type adjustFunction() const;
	
	container_type &container()
	{
		return _values;
	}
	

private:
	Settings(Settings const &cp);
	Settings &operator=(Settings const &cp);

	container_type _values;
	adjfun_type _adjfun;



};





}





#endif // NVX_QT_SETTINGS_47834
