#ifndef QEDITVECTOR_HPP
#define QEDITVECTOR_HPP

#include <functional>
#include <string>

#include <nvx/qt/gui.hpp>
#include <nvx/qt/IWidgets.hpp>
#include <nvx/type.hpp>





namespace nvx
{





class QEditVector: public QWidget
{
Q_OBJECT
public:
	enum Type
	{
		int_type,
		double_type,
		string_type
	};

	/*
	 * members
	 */
	QLabel *sizelabel    = new QLabel("Размер: ");
	QSpinBox *sizeedit   = new QSpinBox;
//	QHBoxLayout *sizelay = new QHBoxLayout;
	QFormLayout *elemlay = new QFormLayout;
//	QVBoxLayout *layout  = new QVBoxLayout;

	std::vector<QWidget *> widgets;
	std::function<std::string(int i)> elemlabelgen =
		[](int i) { return "(" + std::to_string(i+1) + ")"; };


	/*
	 * core
	 */
	QEditVector(Type type = int_type, QWidget *parent = nullptr);
	void resize(int newsize);

	std::function<QWidget *(int)> createNewWidget;
};

inline void get(QEditVector const *widget, std::vector<int> &vec)
{
	auto const &wids = widget->widgets;
	vec.resize(wids.size());
	for(int i = 0; i < (int)wids.size(); ++i)
		get((QSpinBox *)wids[i], vec[i]);
	return;
}

inline void set(QEditVector *widget, std::vector<int> const &vec)
{
	widget->resize(vec.size());
	for(int i = 0; i < (int)vec.size(); ++i)
		set((QSpinBox *)widget->widgets[i], (int)vec[i]);
	return;
}

inline void get(QEditVector const *widget, std::vector<double> &vec)
{
	auto const &wids = widget->widgets;
	vec.resize(wids.size());
	for(int i = 0; i < (int)wids.size(); ++i)
		get((QDoubleSpinBox *)wids[i], vec[i]);
	return;
}

inline void set(QEditVector *widget, std::vector<double> const &vec)
{
	widget->resize(vec.size());
	for(int i = 0; i < (int)vec.size(); ++i)
		set((QDoubleSpinBox *)widget->widgets[i], (int)vec[i]);
	return;
}

inline void get(QEditVector const *widget, std::vector<std::string> &vec)
{
	auto const &wids = widget->widgets;
	vec.resize(wids.size());
	for(int i = 0; i < (int)wids.size(); ++i)
		get((QLineEdit *)wids[i], vec[i]);
	return;
}

inline void set(QEditVector *widget, std::vector<std::string> const &vec)
{
	widget->resize(vec.size());
	for(int i = 0; i < (int)vec.size(); ++i)
		set((QLineEdit *)widget->widgets[i], vec[i]);
	return;
}





}





#endif // QEDITVECTOR_HPP
