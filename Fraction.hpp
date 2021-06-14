#ifndef QUIX_FRACTION_HPP
#define QUIX_FRACTION_HPP

#include <nvx/math.hpp>

// define to disable autoreduce
#ifndef QUIX_NO_FRACTION_AUTOREDUCE
	#define QUIX_FRACTION_AUTOREDUCE
#endif





namespace nvx
{





template<typename T>
struct Fraction
{
	// types
	typedef T value_type;



	// data-members
	value_type a = 0, b = 1;
	
	
	
	
	
	// creation
	Fraction(): a(0), b(1) {}
	Fraction(value_type a): a(a), b(1) {}
	Fraction(value_type a, value_type b): a(a), b(b) {}

	Fraction(float f)
	{
		if(f != f)
			a = 0, b = 0;
		else
			a = f, b = 1; 
		return;
	}
	
	
	
	
	
	// is-functions
	inline bool isNaN() const
	{
		return b == 0;
	}




	// conversion
	template<typename U>
	operator Fraction<U>() const
	{
		return Fraction<U>{a, b};
	}

	operator long double() const
	{
		return (long double)a/b;
	}

	template<typename U>
	Fraction<U> to() const
	{
		return { (U)a, (U)b };
	}



	inline Fraction &operator=(float d)
	{
		if(d != d)
			a = 0, b = 0;
		else
			a = (value_type)d, b = 1;
		return *this;
	}

	template<typename U>
	inline Fraction &operator=(U u)
	{
		a = u;
		b = 1;
		return *this;
	}





	// other
	inline Fraction const &reduce() const
	{
		const_cast<Fraction &>(*this).reduce();
		return *this;
	}
	
	inline Fraction &reduce()
	{
		auto g = gcd(abs(a), b);
		a /= g, b /= g;
		if(a < 0 and b < 0)
			a = -a, b = -b;
		return *this;
	}





	// print/scan
	template<class Ostream>
	Ostream &print( Ostream &os ) const
	{
		os << a << "/" << b;
		return os;
	}

	template<class Istream>
	Istream &scan( Istream &is )
	{
		is >> a >> b;
		return is;
	}
};

template<class Ostream, typename T>
inline Ostream &operator<<( Ostream &os, Fraction<T> const &toprint )
{
	toprint.print(os);
	return os;
}

template<class Istream, typename T>
inline Istream &operator>>( Istream &is, nvx::Fraction<T> &toscan )
{
	toscan.scan(is);
	return is;
}










// ------------------ СРАВНЕНИЕ ---------------------
// with digits
template<typename T, typename U>
inline bool operator==(
	Fraction<T> const &lhs,
	U const &u
)
{
	return lhs.a == u*lhs.b;
}

template<typename T, typename U>
inline bool operator!=(
	Fraction<T> const &lhs,
	U const &u
)
{
	return lhs.a != u*lhs.b;
}

template<typename T, typename U>
inline bool operator<(
	Fraction<T> const &lhs,
	U const &u
)
{
	return lhs.a < u*lhs.b;
}

template<typename T, typename U>
inline bool operator>(
	Fraction<T> const &lhs,
	U const &u
)
{
	return lhs.a > u*lhs.b;
}

template<typename T, typename U>
inline bool operator<=(
	Fraction<T> const &lhs,
	U const &u
)
{
	return lhs < u || lhs == u;
}

template<typename T, typename U>
inline bool operator>=(
	Fraction<T> const &lhs,
	U const &u
)
{
	return lhs > u || lhs == u;
}





template<typename T, typename U>
inline bool operator==(
	U const &u,
	Fraction<T> const &lhs
)
{
	return lhs.a == u*lhs.b;
}

template<typename T, typename U>
inline bool operator!=(
	U const &u,
	Fraction<T> const &lhs
)
{
	return lhs.a != u*lhs.b;
}

template<typename T, typename U>
inline bool operator<(
	U const &u,
	Fraction<T> const &lhs
)
{
	return u*lhs.b < lhs.a;
}

template<typename T, typename U>
inline bool operator>(
	U const &u,
	Fraction<T> const &lhs
)
{
	return u*lhs.b > lhs.a;
}

template<typename T, typename U>
inline bool operator<=(
	U const &u,
	Fraction<T> const &lhs
)
{
	return u < lhs || u == lhs;
}

template<typename T, typename U>
inline bool operator>=(
	U const &u,
	Fraction<T> const &lhs
)
{
	return u > lhs || u == lhs;
}





// with fracitons
template<typename T, typename U>
inline bool operator==(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
#ifdef QUIX_FRACTION_AUTOREDUCE
	return !lhs.isNan() && lhs.a == rhs.a && lhs.b == rhs.b;
#else
	return !lhs.isNan() && !rhs.isNan && lhs / rhs == 1;
#endif
}

template<typename T, typename U>
inline bool operator!=(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	return !(lhs == rhs);
}

template<typename T, typename U>
inline bool operator<(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	return lhs.a*rhs.b < rhs.a*lhs.b;
}

template<typename T, typename U>
inline bool operator>(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	return lhs.a*rhs.b > rhs.a*lhs.b;
}

template<typename T, typename U>
inline bool operator<=(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	return lhs < rhs || lhs == rhs;
}

template<typename T, typename U>
inline bool operator>=(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	return lhs > rhs || lhs == rhs;
}










// -------------- АРИФМЕТИКА ------------------------
// with fraction
template<typename T>
inline Fraction<T> operator-(Fraction<T> const &lhs)
{
	return { -lhs.a, lhs.b };
}



template<typename T, typename U>
inline Fraction<decltype(T()*U())> 
operator+(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	auto l = lcm(lhs.b, rhs.b);
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction{ lhs.a*(l/lhs.b) + rhs.a*(l/rhs.b), l }.reduce();
#else
	return { lhs.a*(l/lhs.b) + rhs.a*(l/rhs.b), l };
#endif
}



template<typename T, typename U>
inline Fraction<decltype(T()*U())> 
operator-(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	auto l = lcm(lhs.b, rhs.b);
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction{ lhs.a*(l/lhs.b) - rhs.a*(l/rhs.b), l }.reduce();
#else
	return { lhs.a*(l/lhs.b) - rhs.a*(l/rhs.b), l };
#endif
}



template<typename T, typename U>
inline Fraction<decltype(T()*U())> 
operator*(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction{ lhs.a*rhs.a, lhs.b*rhs.b  }.reduce();
#else
	return Fraction{ lhs.a*rhs.a, lhs.b*rhs.b  };
#endif
}



template<typename T, typename U>
Fraction<decltype(T()*U())> 
operator/(
	Fraction<T> const &lhs,
	Fraction<U> const &rhs
)
{
	Fraction<U> frac = { lhs.a*rhs.b, lhs.b*rhs.a };
	if(frac.b < 0)
		frac.a = -frac.a,
		frac.b = -frac.b;
#ifdef QUIX_FRACTION_AUTOREDUCE
	frac.reduce();
#endif
	return frac;
}





template<typename T, typename U>
inline Fraction<decltype(T()*U())> &
operator+=(
	Fraction<T> &lhs,
	Fraction<U> const &rhs
)
{
	auto l = lcm(lhs.b, rhs.b);
	lhs.a = lhs.a*(l/lhs.b) + rhs.a*(l/rhs.b);
	lhs.b = l;
#ifdef QUIX_FRACTION_AUTOREDUCE
	lhs.reduce();
#endif
	return lhs;
}



template<typename T, typename U>
inline Fraction<decltype(T()*U())> &
operator-=(
	Fraction<T> &lhs,
	Fraction<U> const &rhs
)
{
	auto l = lcm(lhs.b, rhs.b);
	lhs.a = lhs.a*(l/lhs.b) - rhs.a*(l/rhs.b);
	lhs.b = l;
#ifdef QUIX_FRACTION_AUTOREDUCE
	lhs.reduce();
#endif
	return lhs;
}



template<typename T, typename U>
inline Fraction<decltype(T()*U())> &
operator*=(
	Fraction<T> &lhs,
	Fraction<U> const &rhs
)
{
	lhs.a *= rhs.a;
	lhs.b *= rhs.b;
#ifdef QUIX_FRACTION_AUTOREDUCE
	lhs.reduce();
#endif
	return lhs;
}



template<typename T, typename U>
inline Fraction<decltype(T()*U())> &
operator/=(
	Fraction<T> &lhs,
	Fraction<U> const &rhs
)
{
	lhs.a *= rhs.b;
	lhs.b *= rhs.a;
#ifdef QUIX_FRACTION_AUTOREDUCE
	lhs.reduce();
#endif
	return lhs;
}





// with digits
template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator+(
	Fraction<T> const &frac,
	U u
)
{
	return { frac.a + u*frac.b, frac.b };
}


template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator-(
	Fraction<T> const &frac,
	U u
)
{
	return { frac.a - u*frac.b, frac.b };
}


template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator*(
	Fraction<T> const &frac,
	U u
)
{
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction<decltype(T()*U())>{ frac.a * u, frac.b }.reduce();
#else
	return { frac.a * u, frac.b };
#endif
}


template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator/(
	Fraction<T> const &frac,
	U u
)
{
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction<decltype(T()*U())>{ frac.a, frac.b * u }.reduce();
#else
	return { frac.a, frac.b * u };
#endif
}





template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator+(
	U u,
	Fraction<T> const &frac
)
{
	return { frac.a + u*frac.b, frac.b };
}


template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator-(
	U u,
	Fraction<T> const &frac
)
{
	return { u*frac.b - frac.a, frac.b };
}


template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator*(
	U u,
	Fraction<T> const &frac
)
{
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction<decltype(T()*U())>{ frac.a * u, frac.b }.reduce();
#else
	return { frac.a * u, frac.b };
#endif
}


template<typename T, typename U>
inline Fraction<decltype(T()*U())>
operator/(
	U u,
	Fraction<T> const &frac
)
{
#ifdef QUIX_FRACTION_AUTOREDUCE
	return Fraction<decltype(T()*U())>{ u * frac.b, frac.a }.reduce();
#else
	return { u * frac.b, frac.a };
#endif
}




	// modify
template<typename T, typename U>
inline Fraction<T> &
operator+=(
	Fraction<T> &frac,
	U u
)
{
	frac.a += u*frac.b;
	return frac;
}


template<typename T, typename U>
inline Fraction<T> &
operator-=(
	Fraction<T> &frac,
	U u
)
{
	frac.a -= u*frac.b;
	return frac;
}


template<typename T, typename U>
inline Fraction<T> &
operator*=(
	Fraction<T> &frac,
	U u
)
{
	frac.a *= u;
#ifdef QUIX_FRACTION_AUTOREDUCE
	frac.reduce();
#endif
	return frac;
}


template<typename T, typename U>
inline Fraction<T> &
operator/=(
	Fraction<T> &frac,
	U u
)
{
	frac.b *= u;
#ifdef QUIX_FRACTION_AUTOREDUCE
	frac.reduce();
#endif
	return frac;
}





// typedefs
typedef Fraction<int> FractionI;
typedef Fraction<long long> FractionLL;
typedef Fraction<float> FractionF;
typedef Fraction<double> FractionD;







}





#endif
