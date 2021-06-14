#include <nvx/qt/QEditVector.hpp>

using namespace nvx;





QEditVector::QEditVector(Type type, QWidget *parent) : QWidget(parent)
{
//	layout->addLayout(sizelay);
//	layout->setMargin(0);
//	sizelay->setMargin(0);
//	sizelay->addWidget(sizelabel);
//	sizelay->addWidget(sizeedit);
//	sizeedit->setFixedWidth(60);
//	connect(
//		sizeedit, (void (QSpinBox::*)(int))&QSpinBox::valueChanged,
//		[&](int i) { resize(i); }
//	);
	
//	layout->addLayout(elemlay);
//	elemlay->setMargin(0);
//	elemlay->setHorizontalSpacing(20);
//	resize(3);
	
//	layout->addStretch(1);
	
//	setLayout(layout);
	
	setLayout(elemlay);
	elemlay->addRow(sizelabel, sizeedit);
	sizeedit->setFixedWidth(60);
	connect(
		sizeedit, (void (QSpinBox::*)(int))&QSpinBox::valueChanged,
		[&](int i) { resize(i); }
	);
	
	elemlay->setMargin(0);
	elemlay->setHorizontalSpacing(20);
	setLayout(elemlay);
	
	switch(type)
	{
	case int_type:	
		createNewWidget =
			[](int)->QSpinBox * {
				auto *box = new QSpinBox;
				box->setMinimum(int_min);
				box->setMaximum(int_max);
				box->setFixedWidth(60);
				return box;
			};
		break;
		
	case double_type:
		createNewWidget =
			[](int)->QDoubleSpinBox * {
				auto *box = new QDoubleSpinBox;
				box->setMinimum(-double_inf);
				box->setMaximum(double_inf);
				box->setSingleStep(0.1);
				box->setFixedWidth(60);
				return box;
			};
		break;
		
	case string_type:
		createNewWidget =
			[](int)->QLineEdit * {
				auto *line = new QLineEdit;
				return line;
			};
		break;
	}
	
	resize(3);
	
	return;
}

void QEditVector::resize(int newsize)
{
	if(sizeedit->value() != newsize)
	{
		sizeedit->setValue(newsize);
		return;
	}

	if(newsize == (int)widgets.size())
		return;
		
	if(newsize < (int)widgets.size())
	{
		while((int)widgets.size() != newsize)
		{
			elemlay->removeRow((int)widgets.size());
			widgets.pop_back();
		}
		return;
	}
	
	QWidget *widget;
	while((int)widgets.size() != newsize)
	{
		widget = createNewWidget(widgets.size());
		elemlay->addRow( elemlabelgen(widgets.size()).c_str(), widget );
		widgets.push_back(widget);
	}
	return;
}





// end
