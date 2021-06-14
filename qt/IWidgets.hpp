#ifndef NVX_IWIDGETS_HPP_80192
#define NVX_IWIDGETS_HPP_80192

#include <iostream>
#include <vector>
#include <unordered_map>
#include <nvx/qt/gui.hpp>





namespace nvx
{





/*
 * Assiciations:
 * 		bool...........QCheckBox
 * 		int............inBox
 *      double.........QDoubleSpinBox
 *      string.........QLineEdit
 * 		longstr_type...QTextEdit (longcstr_type)
 */

typedef std::unordered_map< std::string, void * > iwidgets_type; 
typedef struct { std::string s; } lstring;

template<class Ostream>
Ostream &operator<<(Ostream &os, lstring const &s)
{
	os << s.s;
	return os;
}





/*
 * SET FUNCTIONS
 */
inline void set(QCheckBox *widget, bool obj)
{
	widget->setChecked(obj);
	return;
}

inline void set(QSpinBox *widget, int obj)
{
	widget->setValue(obj);
	return;
}

inline void set(QDoubleSpinBox *widget, double obj)
{
	widget->setValue(obj);
	return;
}

inline void set(QLineEdit *widget, std::string const &obj)
{
	widget->setText(obj.c_str());
	return;
}

inline void set(QTextEdit *widget, std::string const &s)
{
	widget->setText(s.c_str());
	return;
}

inline void set(QComboBox *widget, int obj)
{
	widget->setCurrentIndex(obj);
	return;
}

inline void set(QComboBox *widget, std::string const &obj)
{
	widget->setCurrentText(obj.c_str());
	return;
}

inline void set(std::vector<QRadioButton *> *rads, int obj)
{
	if(obj < 0)
	{
		for(auto b = rads->begin(), e = rads->end(); b != e; ++b)
			(*b)->setChecked(false);
		return;
	}
	rads->at(obj)->setChecked(true);
	return;
}

inline void set(std::vector<QCheckBox *> *boxes, std::vector<bool> const &obj)
{
	for(int i = 0; i < (int)boxes->size(); ++i)
		(*boxes)[i]->setChecked(obj[i]);
	return;
}

inline void set(std::vector<QCheckBox *> *boxes, std::vector<std::string> const &obj)
{
	for(auto b = boxes->begin(), e = boxes->end(); b != e; ++b)
	{
		(*b)->setChecked( std::find(
			obj.begin(), obj.end(),
			(*b)->text().toStdString()
		) != obj.end() );
	}
	return;
}

inline void set(std::vector<QCheckBox *> *boxes, int obj)
{
	for(int i = 0; i < (int)boxes->size(); ++i)
		(*boxes)[i]->setChecked( obj & (1 << i) );
	return;
}




template<typename T, typename U>
void set(iwidgets_type &widgets, std::string const &name, T const &obj)
{
	set((U)widgets.at(name), obj);
	return;
}





/*
 * GET FUNCTIONS
 */
inline void get(QCheckBox const *widget, bool &obj)
{
	obj = widget->isChecked();
	return;
}

inline void get(QSpinBox const *widget, int &obj)
{
	obj = widget->value();
	return;
}

inline void get(QDoubleSpinBox const *widget, double &obj)
{
	obj = widget->value();
	return;
}

inline void get(QLineEdit const *widget, std::string &obj)
{
	obj = widget->text().toStdString();
	return;
}

inline void get(QTextEdit const *widget, std::string &obj)
{
	obj = widget->toPlainText().toStdString();
	return;
}

inline void get(QComboBox const *widget, int &obj)
{
	obj = widget->currentIndex();
	return;
}

inline void get(QComboBox const *widget, std::string &obj)
{
	obj = widget->currentText().toStdString();
	return;
}

inline void get(std::vector<QRadioButton *> const *rads, int &obj)
{
	for(int i = 0; i < (int)rads->size(); ++i)
	{
		if((*rads)[i]->isChecked())
		{
			obj = i;
			return;
		}
	}
	obj = -1;
	return;
}

inline void get(std::vector<QCheckBox *> const *boxes, std::vector<bool> &obj)
{
	obj.resize(boxes->size());
	for(int i = 0; i < (int)boxes->size(); ++i)
		obj[i] = (*boxes)[i]->isChecked();
	return;
}

inline void get(std::vector<QCheckBox *> const *boxes, std::vector<std::string> &obj)
{
	obj.clear();
	for(auto b = boxes->begin(), e = boxes->end(); b != e; ++b)
	{
		if((*b)->isChecked())
			obj.push_back((*b)->text().toStdString());
	}
	return;
}

inline void get(std::vector<QCheckBox *> const *boxes, int &obj)
{
	obj = ( 1 << boxes->size() ) - 1;
	for(int i = 0; i < (int)boxes->size(); ++i)
		obj &= ( 1 << i ) * ((*boxes)[i]->isChecked() ? 1 : 0);
	return;
}



template<typename T, typename U>
void get(iwidgets_type const &widgets, std::string const &name, T &obj)
{
	get((U)widgets.at(name), obj);
	return;
}

template<typename T, typename U>
T get(iwidgets_type const &widgets, std::string const &name)
{
	T obj;
	get<T, U>(widgets, name, obj);
	return obj;
}





}





#endif
