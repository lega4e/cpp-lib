#ifndef SWBRIDGE_HPP_73902
#define SWBRIDGE_HPP_73902

#include <iostream>
#include <tuple>

#include <nvx/iostream.hpp>
#include <nvx/macro.hpp>
#include <nvx/TypeList.hpp>
#include <nvx/qt/IWidgets.hpp>
#include <nvx/Settings.hpp>





namespace nvx
{





/*
 * content functions
 */
template<typename T, typename U>
inline void _setting_to_widget(
	char const *name,
	std::tuple<nvx::Settings const &, iwidgets_type &> arg
)
{
	set<T, U>(get<1>(arg), name, get<0>(arg).get<T>(name));
	return;
}

template<typename T, typename U>
inline void _widget_to_setting(
	char const *name,
	std::tuple<nvx::Settings &, iwidgets_type const &> arg
)
{
	T obj;
	get<T, U>(get<1>(arg), name, obj);
	get<0>(arg).set(name, obj);
	return;
}

template<typename T, typename U>
inline void _print_setting(
	char const *name,
	nvx::Settings const &sets
)
{
	std::cout << name << ": \t";
	nvx::print(std::cout, sets.get<T>(name)) << '\n';
	return;
}

template<typename T, typename U>
inline void _print_widget(
	char const *name,
	iwidgets_type const &widgets
)
{
	std::cout << name << ": \t" << get<T, U>(widgets, name) << '\n';
	return;
}



/*
 * Macros functions
 */
NVX_DEFINE_TYPE_LIST_FOREACH_FUNCTION(
	_settings_to_widgets, _setting_to_widget,
	ARG(std::tuple<nvx::Settings const &, iwidgets_type &>)
)

NVX_DEFINE_TYPE_LIST_FOREACH_FUNCTION(
	_widgets_to_settings, _widget_to_setting,
	ARG(std::tuple<nvx::Settings &, iwidgets_type const &>)
)

NVX_DEFINE_TYPE_LIST_FOREACH_FUNCTION(
	print, _print_setting, nvx::Settings const &
)

NVX_DEFINE_TYPE_LIST_FOREACH_FUNCTION(
	print, _print_widget, iwidgets_type const &
)



/*
 * Alias functions
 */
template<typename...Args>
inline void settings_to_widgets(
	nvx::TypeList<Args...> list,
	nvx::Settings const &sets,
	iwidgets_type &widgets
)
{
	_settings_to_widgets(list, tie(sets, widgets));
	return;
}

template<typename...Args>
inline void widgets_to_settings(
	nvx::TypeList<Args...> list,
	iwidgets_type const &widgets,
	nvx::Settings &sets
)
{
	_widgets_to_settings(list, tie(sets, widgets));
	return;
}

template<typename...Args>
void print(nvx::TypeList<Args...> list, nvx::Settings const &sets);

template<typename...Args>
void print(nvx::TypeList<Args...> list, iwidgets_type const &sets);





}





#endif
