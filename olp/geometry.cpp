#define _USE_MATH_DEFINES
#include <cmath>

#include <nvx/type.hpp>







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
inline bool belongs(Point p, Straight s)
{
	return fabs(s.a*p.x + s.b*p.y - s.c) < ALPHA;
}


inline bool belongs(Point p, Point a, Point b)
{
	return
		// x1 <= x <= x2
		std::min(a.x, b.x) - p.x < ALPHA &&
		p.x - std::max(a.x, b.x) < ALPHA &&

		// y1 <= y <= y2
		std::min(a.y, b.y) - p.y < ALPHA &&
		p.y - std::max(a.y, b.y) < ALPHA &&

		// on a straight
		belongs(p, tostraight(a, b));
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
int belongs(Point p, Point a, Point b, Point c)
{
	int  const ab     = which_side(p, a, b);
	int  const bc     = which_side(p, b, c);
	int  const ac     = which_side(p, a, c);
	bool const onside = !ab or !bc or !ac;

	return
		( !ab or ab == which_side(c, a, b) ) and
		( !bc or bc == which_side(a, b, c) ) and
		( !ac or ac == which_side(b, a, c) ) ?
			(onside ? 1 : 2) : 0;
}



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
int intersects(Point c1, ldouble r1, Point c2, ldouble r2)
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
