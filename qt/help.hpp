#ifndef NVX_QT_HELP_HPP
#define NVX_QT_HELP_HPP

#include <nvx/qt/gui.hpp>

#include <QGuiApplication>
#include <QScreen>





namespace nvx
{





inline QWidget *makeLayoutedWidget(QLayout *layout)
{
	QWidget *widget = new QWidget;
	widget->setLayout(layout);
	return widget;
}


// dpi = QGuiApplication::primaryScreen()->physicalDotsPerInch()
inline double pttopx(double pt, double dpi = -1)
{
    return pt / 72 * (
    	dpi > 0 ? dpi :
    		QGuiApplication::primaryScreen()->physicalDotsPerInch()
    );
}


inline double pxtopt(double px, double dpi = -1)
{
    return px * 72 / (
    	dpi > 0 ? dpi :
    		QGuiApplication::primaryScreen()->physicalDotsPerInch()
    );
}



/* META */
struct QWA
{
	QWidget *widget;
	int stretch = 0;
	Qt::Alignment align = Qt::Alignment();
};

struct QLA
{
	QLayout *layout;
	int stretch = 0;
};

struct QSPA
{
	int space = 5;
};

struct QSTA
{
	int stretch = 1;
};

inline void add(QBoxLayout *) {}

template<typename...Args>
void add(QBoxLayout *layout, QWidget *widget, Args...args);

template<typename...Args>
void add(QBoxLayout *layout, QWidget *widget, int st, Args...args);

template<typename...Args>
void add(QBoxLayout *layout, QWidget *widget, Qt::AlignmentFlag align, Args...args);

template<typename...Args>
void add(
	QBoxLayout *layout,
	QWidget *widget, int st,
	Qt::AlignmentFlag align, Args...args
);

template<typename...Args>
void add(QBoxLayout *layout, QLayout *lay, Args...args);

template<typename...Args>
void add(QBoxLayout *layout, QWA const &widget, Args...args);

template<typename...Args>
void add(QBoxLayout *layout, QLA const &lay, Args...args);

template<typename...Args>
void add(QBoxLayout *layout, QSPA const &widget, Args...args);

template<typename...Args>
void add(QBoxLayout *layout, QSTA const &lay, Args...args);



template<typename...Args>
void add(QBoxLayout *layout, QWidget *widget, Args...args)
{
	layout->addWidget(widget);
	add(layout, args...);
	return;
}

template<typename...Args>
void add(QBoxLayout *layout, QWidget *widget, int st, Args...args)
{
	layout->addWidget(widget, st);
	add(layout, args...);
}

template<typename...Args>
void add(QBoxLayout *layout, QWidget *widget, Qt::AlignmentFlag align, Args...args)
{
	layout->addWidget(widget, 0, align);
	add(layout, args...);
}

template<typename...Args>
void add(
	QBoxLayout *layout,
	QWidget *widget, int st,
	Qt::AlignmentFlag align, Args...args
)
{
	layout->addWidget(widget, st, align);
	add(layout, args...);
}

template<typename...Args>
void add(QBoxLayout *layout, QLayout *lay, Args...args)
{
	layout->addLayout(lay);
	add(layout, args...);
	return;
}

template<typename...Args>
void add(QBoxLayout *layout, QWA const &widget, Args...args)
{
	layout->addWidget(widget.widget, widget.stretch, widget.align);
	add(layout, args...);
	return;
}


template<typename...Args>
void add(QBoxLayout *layout, QLA const &lay, Args...args)
{
	layout->addLayout(lay.layout, lay.stretch);
	add(layout, args...);
	return;
}


template<typename...Args>
void add(QBoxLayout *layout, QSPA const &s, Args...args)
{
	layout->addSpacing(s.space);
	add(layout, args...);
	return;
}


template<typename...Args>
void add(QBoxLayout *layout, QSTA const &s, Args...args)
{
	layout->addStretch(s.stretch);
	add(layout, args...);
	return;
}







}





#endif
