#include <nvx/qt/QCheckBoxList.hpp>

#include <iostream>


using namespace nvx;
using namespace std;





QCheckBoxList::QCheckBoxList(QWidget *parent): QWidget(parent) {}

QCheckBoxList::QCheckBoxList(
	std::vector<std::string> const &labels,
	QWidget *parent
): QWidget(parent)
{
	set(labels);
	return;
}

QCheckBoxList::QCheckBoxList(
	std::vector<std::pair<std::string, bool>> const &labels,
	QWidget *parent
): QWidget(parent)
{
	set(labels);
	return;
}


void QCheckBoxList::set(std::vector<std::string> const &labels)
{
	if(layout)
		delete layout;
	layout = new QVBoxLayout();
	layout->setMargin(0);

	QCheckBox *box;
	for(auto b = labels.begin(), e = labels.end(); b != e; ++b)
	{
		box = new QCheckBox(b->c_str());
		layout->addWidget(box);
		boxes.push_back(box);
	}
	layout->addStretch(1);

	setLayout(layout);
	return;
}

void QCheckBoxList::set(std::vector<std::pair<std::string, bool>> const &labels)
{
	if(layout)
		delete layout;
	layout = new QVBoxLayout();
	layout->setMargin(0);

	QCheckBox *box;
	for(auto b = labels.begin(), e = labels.end(); b != e; ++b)
	{
		box = new QCheckBox(b->first.c_str());
		box->setChecked(b->second);
		layout->addWidget(box);
		boxes.push_back(box);
	}
	layout->addStretch(1);

	setLayout(layout);
	return;}





// end
