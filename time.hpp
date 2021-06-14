#ifndef NVX_TIME_HPP
#define NVX_TIME_HPP

#include <ctime>
#include <cstring>
#include <string>





namespace nvx
{





/*
 *
 * DATE
 * %d.....День месяца (1-31)
 * %m.....Месяц года (1-12)
 * %y.....Год (две последние цифры)
 * %Y.....Год (четыре цифры)
 *
 * $m.....Название месяца на русском (со строчной)
 * $M.....Название месяца на русском (с прописной)
 *
 * $w.....Название дня недели на русском (со строчной)
 * $W.....Название дня недели на русском (с прописной)
 *
 *
 * TIME
 * %X.....Время в формате HH:MM:SS (20:01:59)
 * %R.....Время в формате HH:MM (20:01)
 * %S.....Секунды (00-59)
 * %M.....Минуты (00-59)
 * %H.....Часы (00-23)
 *
 */

constexpr char const *timefmt_date = "%d.%m.%Y";
constexpr char const *timefmt_full = "%d.%m.%Y, %X";

constexpr char const *timefmt_reverse = "%Y.%m.%d";
constexpr char const *timefmt_fullreverse = "%Y.%m.%d, %X";

constexpr char const *months_rus[] = {
	"Январь",
	"Февраль",
	"Март",
	"Апрель",
	"Май",
	"Июнь",
	"Июль",
	"Август",
	"Сентябрь",
	"Октябрь",
	"Ноябрь",
	"Декабрь"
};

constexpr char const *months_rus_lower[] = {
	"январь",
	"февраль",
	"март",
	"апрель",
	"май",
	"июнь",
	"июль",
	"август",
	"сентябрь",
	"октябрь",
	"ноябрь",
	"декабрь"
};

constexpr char const *weekdays_rus[] = {
	"Понедельник",
	"Вторник",
	"Среда",
	"Четверг",
	"Пятница",
	"Суббота",
	"Воскресение"
};

constexpr char const *weekdays_rus_lower[] = {
	"понедельник",
	"вторник",
	"среда",
	"четверг",
	"пятница",
	"суббота",
	"воскресение"
};

std::string ftime(char const *fmt, time_t time = -1);





}





#endif
