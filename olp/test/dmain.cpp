#include <iostream>
#include <fstream>

#define _USE_MATH_DEFINES
#include <cmath>

#ifndef NVX_TYPE_HPP
#define NVX_TYPE_HPP

#include <limits>



typedef int8_t byte;
typedef uint8_t ubyte;
typedef int64_t llong;
typedef uint64_t ullong;
typedef long double ldouble;


constexpr int  const int_inf  = std::numeric_limits<int>::max() / 2;
constexpr int  const int_max  = std::numeric_limits<int>::max();
constexpr int  const int_min  = std::numeric_limits<int>::min();
constexpr long const long_inf = std::numeric_limits<long>::max() / 2;
constexpr long const long_max = std::numeric_limits<long>::max();
constexpr long const long_min = std::numeric_limits<long>::min();

constexpr llong  const llong_inf  = std::numeric_limits<llong>::max() / 2;
constexpr llong  const llong_max  = std::numeric_limits<llong>::max();
constexpr llong  const llong_min  = std::numeric_limits<llong>::min();
constexpr ullong const ullong_inf = std::numeric_limits<ullong>::max() / 2;
constexpr ullong const ullong_max = std::numeric_limits<ullong>::max();
constexpr ullong const ullong_min = std::numeric_limits<ullong>::min();

constexpr float   const float_inf    = std::numeric_limits<float>::infinity();
constexpr float   const float_nan    = std::numeric_limits<float>::quiet_NaN();
constexpr float   const float_snan   = std::numeric_limits<float>::signaling_NaN();

constexpr double  const double_inf   = std::numeric_limits<double>::infinity();
constexpr double  const double_nan   = std::numeric_limits<double>::quiet_NaN();
constexpr double  const double_snan  = std::numeric_limits<double>::signaling_NaN();

constexpr ldouble const ldouble_inf  = std::numeric_limits<ldouble>::infinity();
constexpr ldouble const ldouble_nan  = std::numeric_limits<ldouble>::quiet_NaN();
constexpr ldouble const ldouble_snan = std::numeric_limits<ldouble>::signaling_NaN();





#endif









// TYPES
typedef struct
{
	ldouble x, y;
} Point, Vector;


/*
 * Представляет из себя прямую, заданную
 * уравнением: a*x + b*y = c
 */
typedef struct
{
	ldouble a, b, c;
} Straight;







// OBJECTS
/*
 * Используется для сравнения на равенство и
 * неравество с учётом погрешности в вычислениях:
 * 	a == b	-> fabs(a - b) < ALPHA
 * 	a != b  -> fabs(a - b) >= ALPHA
 *
 * 	a < b	-> a - b < -ALPHA
 * 	a > b	-> b - a < -ALPHA
 *
 * 	a <= b	-> a - b < ALPHA
 * 	a >= b	-> b - a < ALPHA
 */
constexpr ldouble const ALPHA = 0.000000001;







// ПРОСТЕЙШЕЕ
inline ldouble distance(Point a, Point b)
{
	return sqrt(
		(b.x - a.x) * (b.x - a.x) +
		(b.y - a.y) * (b.y - a.y)
	);
}


inline Vector tovector(Point b, Point e)
{
	return { e.x - b.x, e.y - b.y };
}


inline Vector operator-(Point e, Point b)
{
	return { e.x - b.x, e.y - b.y };
}


inline ldouble length(Vector v)
{
	return sqrt( v.x*v.x + v.y*v.y );
}


inline ldouble rtod(ldouble radians)
{
	return radians * 180.0 / M_PI;
}


inline ldouble dtor(ldouble degrees)
{
	return degrees * M_PI / 180.0;
}







// УГЛЫ
/*
 * 1.cos — вычисляет косинус угола между векторами:
 * от 0-я до 180-ти градусов; показывает насколько
 * угол широк
 *
 * 2.anglec — вычисляет угол по косинусу
 *
 * 3.sin — вычисляет синус угла между векторами,
 * учитывая направление; оно положительно, если
 * против часовой стрелки, иначе — отрицательно
 *
 * 4.angles — вычисляет угол по синусу от -90 до 90,
 * учитывая направление
 */
inline ldouble cos(Vector a, Vector b)
{
	return
 		(ldouble)(a.x*b.x + a.y*b.y) /
		( length(a) * length(b) );
}


inline ldouble anglec(Vector a, Vector b)
{
	return acos(cos(a, b));
}



inline ldouble sin(Vector a, Vector b)
{
	return
		(ldouble)(a.x*b.y - a.y*b.x) /
		( length(a) * length(b) );
}


inline ldouble angles(Vector a, Vector b)
{
	return asin(sin(a, b));
}

/*
 * Возвращает широкий (от 0 до 2pi) угол между
 * двумя векторами (или вектором и осью Ox)
 * против часовой стрелки
 */
inline ldouble anglew( Vector const &a, Vector const &b )
{
	ldouble const asin = sin(a, b);
	ldouble const acos = cos(a, b);
	return asin < 0 ? 2*M_PI - std::acos(acos) : std::acos(acos);
}

inline ldouble anglew( Vector const &a )
{
	return anglew( { 1.0, 0.0 }, a );
}







// ПЛОЩАДИ
/*
 * Вычисляет площадь треугольника по
 * заданным сторонам или точкам вершин,
 * используя формулу Герона; вычисляет
 * площадь простого (не пересекающего
 * себя) многоугольника по заданным
 * вершинам
 */
ldouble area(ldouble a, ldouble b, ldouble c)
{
	ldouble const p = (a + b + c) / 2.0;
	return sqrt(
		p * (p - a) * (p - b) * (p - c)
	);
}

inline ldouble area(Point a, Point b, Point c)
{
	return area(
		distance(a, b),
		distance(b, c),
		distance(c, a)
	);
}

ldouble area(Point const *vers, int n)
{
	ldouble sum = 0.0;
	for(int i = 0; i < n; ++i)
	{
		sum +=
			( vers[i].y + vers[ (i+1)%n ].y ) / 2.0 *
			( vers[ (i+1)%n ].x - vers[i].x );
	}
	return fabs(sum);
}







// ПРЯМЫЕ
/*
 * Находит прямую, проходящую через
 * обе точки; предполагается, что
 * точки различны
 */
Straight tostraight(Point p, Point pp)
{
	Straight s;
	if( fabs(p.y - pp.y) < ALPHA )
	{
		s.b = 1.0;
		s.a = (ldouble)(pp.y - p.y) / (p.x - pp.x);
	}
	else
	{
		s.a = 1.0;
		s.b = (ldouble)(p.x - pp.x) / (pp.y - p.y);
	}
	s.c = p.x + s.b*p.y;
	return s;
}



/*
 * Находит точку пересечения прямых;
 * если такой не существует (т.е. если
 * прямые параллельны), возвращает
 * точку { NAN, NAN }; чтобы проверить,
 * является ли ldouble NAN выполните
 * проверку: NAN == NAN — она всегда
 * ложна
 */
inline Point cross(Straight s, Straight ss)
{
	if( fabs(s.a*ss.b - ss.a*s.b) < ALPHA )
		return { NAN, NAN };
	return {
		-(ldouble)( s.b*ss.c - ss.b*s.c ) /
			(s.a*ss.b - ss.a*s.b),
		(ldouble)( s.a*ss.c - ss.a*s.c ) /
			(s.a*ss.b - ss.a*s.b)
	};
}



/*
 * Проверяет, принадлежит ли точка
 * прямой, отрезку
 */
inline bool belong(Point p, Straight s)
{
	return fabs(s.a*p.x + s.b*p.y - s.c) < ALPHA;
}


inline bool belong(Point p, Point a, Point b)
{
	return
		// x1 <= x <= x2
		std::min(a.x, b.x) - p.x < ALPHA &&
		p.x - std::max(a.x, b.x) < ALPHA &&

		// y1 <= y <= y2
		std::min(a.y, b.y) - p.y < ALPHA &&
 		p.y - std::max(a.y, b.y) < ALPHA &&

		// on a straight
		belong(p, tostraight(a, b));
}

/*
 * Определяет, с какой стороны от прямой
 * находится точка; (направление прямо считается
 * от a до b); -1 — слева, 1 — справа, 0 — на прямой
 */
int which_side(Point p, Point a, Point b)
{
	ldouble res = sin(tovector(a, p), tovector(a, b));
	// cout << res << endl;
	return fabs(res) < ALPHA ? 0 :
		res < 0 ? -1 : 1;
}



/*
 * Определяет, принадлежит ли точка
 * треугольнику; возвращает 1, если
 * точка находится на одной из сторон,
 * 2 — если находится строго внутри
 * треугольника, 0 — если точка
 * строго снаружи треугольника
 */
int belong(
	Point p,
	Point p1, Point p2, Point p3
)
{
	ldouble const
		s  = area(p1, p2, p3),
		s1 = area(p, p2, p3),
		s2 = area(p, p1, p3),
		s3 = area(p, p1, p2);

	if( fabs(s - (s1 + s2 + s3)) < ALPHA )
	{
		if(
			fabs(s1) < ALPHA ||
 			fabs(s2) < ALPHA ||
			fabs(s3) < ALPHA
		)
			return 1;
		else
			return 2;
	}

	return 0;
}
/*
 * int belong(Point p, Point a, Point b, Point c)
 * {
 *     int  const ab     = which_side(p, a, b);
 *     int  const bc     = which_side(p, b, c);
 *     int  const ac     = which_side(p, a, c);
 *     bool const onside = !ab or !bc or !ac;
 *
 *     return
 *         ( !ab or ab == which_side(c, a, b) ) and
 *         ( !bc or bc == which_side(a, b, c) ) and
 *         ( !ac or ac == which_side(b, a, c) ) ?
 *             (onside ? 1 : 2) : 0;
 * }
 */



/*
 * Строит прямую, параллельную/перпендикулярную
 * данной и проходяющую через данную точку
 */
inline Straight parallel(Straight s, Point p)
{
	return { s.a, s.b, s.a*p.x + s.b*p.y };
}


inline Straight perpend(Straight s, Point p)
{
	return
 		fabs(s.a) < ALPHA ? Straight{ 1.0, 0.0, p.x } :
		fabs(s.b) < ALPHA ? Straight{ 0.0, 1.0, p.y } :
		Straight{
			1.0, -(ldouble)s.a/s.b,
 			p.x - (ldouble)s.a/s.b*p.y
		};
}







// ОКРУЖНОСТИ
/*
 * Определяет, сколько общих точек
 * имеют окружности
 */
int area(Point c1, ldouble r1, Point c2, ldouble r2)
{
	ldouble const sql =
		(c2.x - c1.x) * (c2.x - c1.x) +
		(c2.y - c1.y) * (c2.y - c1.y);

	if( fabs( sql - (r1 + r2)*(r1 + r2) ) < ALPHA )
		return 1;
	if(
		sql - (r1 + r2)*(r1 + r2) < ALPHA &&
		(r1 - r2)*(r1 - r2) - sql < ALPHA
	)
		return 2;
	return 0;
}







// end



using namespace std;





// main
int main( int argc, char *argv[] )
{
	Point a, b, c, p;
	cin >>
 		a.x >> a.y >>
		b.x >> b.y >>
		c.x >> c.y >>
		p.x >> p.y;

	if( belong(p, a, b, c) )
		cout << "In" << endl;
	else
		cout << "Out" << endl;


	return 0;
}





// end
