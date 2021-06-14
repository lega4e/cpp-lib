#ifndef QCHECKBOXLIST_HPP
#define QCHECKBOXLIST_HPP

#include <nvx/qt/gui.hpp>
#include <nvx/qt/IWidgets.hpp>

#include <string>
#include <vector>





namespace nvx
{ 





class QCheckBoxList: public QWidget
{
Q_OBJECT
public:
	QVBoxLayout *layout = nullptr;
	std::vector<QCheckBox *> boxes;

	QCheckBoxList(QWidget *parent = nullptr);
	QCheckBoxList(std::vector<std::string> const &labels, QWidget *parent = nullptr);
	QCheckBoxList(
		std::vector<std::pair<std::string, bool>> const &labels,
		QWidget *parent = nullptr
	);
	
	void set(std::vector<std::string> const &labels);
	void set(std::vector<std::pair<std::string, bool>> const &labels);
	
	
};



inline void set(QCheckBoxList *widget, std::vector<bool> const &obj)
{
	set(&widget->boxes, obj);
	return;
}

inline void set(QCheckBoxList *widget, std::vector<std::string> const &obj)
{
	set(&widget->boxes, obj);
	return;
}

inline void set(QCheckBoxList *widget, int obj)
{
	set(&widget->boxes, obj);
}



inline void get(QCheckBoxList const *widget, std::vector<bool> &obj)
{
	get(&widget->boxes, obj);
	return;
}

inline void get(QCheckBoxList const *widget, std::vector<std::string> &obj)
{
	get(&widget->boxes, obj);
	return;
}

inline void get(QCheckBoxList const *widget, int &obj)
{
	get(&widget->boxes, obj);
	return;
}





}





#endif // QCHECKBOXLIST_HPP
