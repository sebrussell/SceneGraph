// vector.h

#pragma once

#include <math.h>
#include <cmath>
#include <limits>
#include <iostream>

namespace Math3d {

template<class T> class Vector3D {

public:
    Vector3D(T _x = 0, T _y = 0, T _z = 0);
    Vector3D(const Vector3D<T> & _v);
    Vector3D(const Vector3D<T> & _from, const Vector3D<T> & _to);
    ~Vector3D();

    void set(T _x, T _y, T _z);
    
    Vector3D<T> operator+(const Vector3D<T> & _v) const;
    Vector3D<T> operator-(const Vector3D<T> & _v) const;
    T operator*(const Vector3D<T> & _v) const;

    Vector3D<T> operator^(const Vector3D<T> & _v) const;
	static void cross(const Vector3D<T>& A, const Vector3D<T>& B, Vector3D<T>& R);

	Vector3D<T> mult(const Vector3D<T> & _v) const;
    Vector3D<T> operator*(T _d) const;
    Vector3D<T> operator/(T _d) const;

    Vector3D<T> & operator=(const Vector3D<T> & _v);
    Vector3D<T> & operator+=(const Vector3D<T> & _v);
    Vector3D<T> & operator-=(const Vector3D<T> & _v);
    Vector3D<T> & operator*=(T _d);
    Vector3D<T> & operator/=(T _d);
    Vector3D<T> operator-();

    Vector3D<T> getUnit() const;
    Vector3D<T> & normalize();
	Vector3D<T> & safe_normalize();
   
	void computeComplementBasis(Vector3D<T>& out_U, Vector3D<T>& out_V) const;

    T length() const;
    T length2() const;
    T distance(const Vector3D<T> & _v) const;
    T distance2(const Vector3D<T> & _v) const;

    Vector3D<T> rotateX(T cosa, T sina) const;
    Vector3D<T> rotateY(T cosa, T sina) const;
    Vector3D<T> rotateZ(T cosa, T sina) const;
    Vector3D<T> rotate(const Vector3D<T> & _axe, T cosa, T sina) const;
    
	bool isInfinite() const;
	bool isNaN() const;

    T x, y, z;
};

template<class T> Vector3D<T>::Vector3D(T _x, T _y, T _z) : x(_x), y(_y), z(_z)
{
};

template<class T> Vector3D<T>::Vector3D(const Vector3D<T> & _v) : x(_v.x), y(_v.y), z(_v.z)
{
};

template<class T> Vector3D<T>::Vector3D(const Vector3D<T> & _from, const Vector3D<T> & _to) : x(_to.x - _from.x), y(_to.y - _from.y), z(_to.z - _from.z)
{
};

template<class T> Vector3D<T>::~Vector3D()
{
};

template<class T> bool Vector3D<T>::isInfinite() const
{
	
	if( x==std::numeric_limits<T>::infinity() ) return true;
	if( y==std::numeric_limits<T>::infinity() ) return true;
	if( z==std::numeric_limits<T>::infinity() ) return true;
	return false;
}
template<class T> bool Vector3D<T>::isNaN() const
{
	if( x!=x ) return true;
	if( y!=y ) return true;
	if( z!=z ) return true;
	return false;
}

template<class T> void Vector3D<T>::set(T _x, T _y, T _z)
{
    x=_x;
    y=_y;
    z=_z;
};

template<class T> Vector3D<T> Vector3D<T>::operator+(const Vector3D<T> & _v) const
{
    return Vector3D(x+_v.x, y+_v.y, z+_v.z);
};
template<class T> Vector3D<T> Vector3D<T>::mult(const Vector3D<T> & _v) const
{
	return Vector3D(x*_v.x, y*_v.y, z*_v.z);
}
template<class T> Vector3D<T> Vector3D<T>::operator-(const Vector3D<T> & _v) const
{
    return Vector3D(x-_v.x, y-_v.y, z-_v.z);
}

template<class T> T Vector3D<T>::operator*(const Vector3D<T> & _v) const
{
    return x*_v.x + y*_v.y + z*_v.z;
};

template<class T> Vector3D<T> Vector3D<T>::operator^(const Vector3D<T> & _v) const
{
    return Vector3D<T>( y*_v.z - _v.y*z, z*_v.x - _v.z*x, x*_v.y - _v.x*y );
};
template<class T> 
void Vector3D<T>::cross(const Vector3D<T>& A, const Vector3D<T>& B, Vector3D<T>& R)
{
	R.set(  A.y*B.z - B.y*A.z, A.z*B.x - B.z*A.x, A.x*B.y - B.x*A.y );
}

template<class T> Vector3D<T> Vector3D<T>::operator*(T _d) const
{
    return Vector3D<T>(x*_d, y*_d, z*_d);
};

template<class T> Vector3D<T> Vector3D<T>::operator/(T _d) const
{
    return Vector3D<T>(x/_d, y/_d, z/_d);
};

template<class T> Vector3D<T> & Vector3D<T>::operator=(const Vector3D<T> & _v)
{
    x=_v.x;
    y=_v.y;
    z=_v.z;
    return *this;
};

template<class T> Vector3D<T> & Vector3D<T>::operator+=(const Vector3D<T> & _v)
{
    x+=_v.x;
    y+=_v.y;
    z+=_v.z;
    return *this;
};

template<class T> Vector3D<T> & Vector3D<T>::operator-=(const Vector3D<T> & _v)
{
    x-=_v.x;
    y-=_v.y;
    z-=_v.z;
    return *this;
};

template<class T> Vector3D<T> & Vector3D<T>::operator*=(T _d)
{
    x*=_d;
    y*=_d;
    z*=_d;
    return *this;
};

template<class T> Vector3D<T> & Vector3D<T>::operator/=(T _d)
{
    x/=_d;
    y/=_d;
    z/=_d;
    return *this;
};

template<class T> Vector3D<T> Vector3D<T>::operator-()
{
    return Vector3D<T>(-x, -y, -z);
};

template<class T> Vector3D<T> Vector3D<T>::getUnit() const
{
    T length(sqrt(x*x + y*y + z*z));
    return Vector3D<T>(x/length, y/length, z/length);
};

template<class T> Vector3D<T> & Vector3D<T>::normalize()
{
    T length = sqrt(x*x + y*y + z*z);
	if (length>0.00001)
	{
		x/=length;
		y/=length;
		z/=length;
	}
    return *this;
};
template<class T> Vector3D<T> & Vector3D<T>::safe_normalize()
{
	T length_sq = (x*x + y*y + z*z);
	if (length_sq>0.00001)
	{
		T lengthinv = T(1)/sqrt(length_sq);
		x*=lengthinv;
		y*=lengthinv;
		z*=lengthinv;
	}
    return *this;
};

template<class T> T Vector3D<T>::length() const
{
    return sqrt(x*x + y*y + z*z);
};

template<class T> T Vector3D<T>::length2() const
{
    return x*x + y*y + z*z;
};

template<class T> T Vector3D<T>::distance(const Vector3D<T> & _v) const
{
    T tx(_v.x-x);
    T ty(_v.y-y);
    T tz(_v.z-z);
    return sqrt(tx*tx + ty*ty + tz*tz);
};

template<class T> T Vector3D<T>::distance2(const Vector3D<T> & _v) const
{
    T tx(_v.x-x);
    T ty(_v.y-y);
    T tz(_v.z-z);
    return tx*tx + ty*ty + tz*tz;
};

template<class T> Vector3D<T> Vector3D<T>::rotateX(T cosa, T sina) const
{
    return Vector3D<T>( x, cosa*y-sina*z, sina*y+cosa*z);
};

template<class T> Vector3D<T> Vector3D<T>::rotateY(T cosa, T sina) const
{
    return Vector3D<T>( cosa*x+sina*z, y, cosa*z-sina*x);
};

template<class T> Vector3D<T> Vector3D<T>::rotateZ(T cosa, T sina) const
{
    return Vector3D<T>( cosa*x-sina*y, sina*x+cosa*y, z);
};

template<class T> Vector3D<T> Vector3D<T>::rotate(const Vector3D<T> & _axe, T cosa, T sina) const
{
    return ((*this)*cosa) + (_axe*((1.0-cosa)*((*this)*_axe))) + ((_axe^(*this))*sina);
};

template<class T>
void Vector3D<T>::computeComplementBasis(Vector3D<T>& out_U, Vector3D<T>& out_V) const
{
    T invLength;

		if( abs(this->x) >= abs(this->y) )
		{
			// W.x or W.z is the largest magnitude component, swap them
			invLength = 1/sqrt(this->x*this->x + this->z*this->z);
			out_U.x = -this->z*invLength;
			out_U.y = 0;
			out_U.z = +this->x*invLength;
		}
		else
		{
			// W.y or W.z is the largest magnitude component, swap them
			invLength = 1/sqrt(this->y*this->y + this->z*this->z);
			out_U.x = 0;
			out_U.y = +this->z*invLength;
			out_U.z = -this->y*invLength;
		}
		out_V = *this^out_U;
}

//};//namespace Math3d


//using std::min;
//using std::max;
//using std::swap;

template<class T> 
class Vector2D
{
	public:

	   Vector2D(T _x = 0, T _y = 0);
	   Vector2D(const Vector2D<T> & _v);
	   Vector2D(const Vector2D<T> & _from, const Vector2D<T> & _to);

	   ~Vector2D();

	   Vector2D<T> operator+=(const Vector2D<T> &w);
	   Vector2D<T> operator-=(const Vector2D<T> &w);
	   T length2(const Vector2D<T> &a);
	   T length(const Vector2D<T> &a);
	   T length() const;
	   T dist2(const Vector2D<T> &a, const Vector2D<T> &b);
	   T dist(const Vector2D<T> &a, const Vector2D<T> &b);
	   bool operator==(const Vector2D<T> &a);
	   bool operator!=(const Vector2D<T> &a);
	   Vector2D<T> operator-(const Vector2D<T> &a);
	   Vector2D<T> operator+(const Vector2D<T> &a);
	   Vector2D<T> operator-();
	   Vector2D<T> operator*(const T scalar);
	   Vector2D<T> operator/(const T scalar);
	  
	   T dot(const Vector2D<T> &a, const Vector2D<T> &b);
	   T cross(const Vector2D<T>&a, const Vector2D<T> &b);
	   Vector2D<T> perp(const Vector2D<T> &a);
	   Vector2D<T> normalize(const Vector2D<T> &a) ;
	   Vector2D<T> & normalize() const;
	   void normalize();
	   Vector2D<T> mult(T scalar, const Vector2D<T> &a);

	//   std::ostream  &operator<<(std::ostream &out, const Vector2D<T> &a);
   //    std::istream  &operator>>(std::istream &in, Vector2D<T> &a);

	   T x, y;

};


template<class T> Vector2D<T>::Vector2D(T _x, T _y) : x(_x), y(_y)
{
};

template<class T> Vector2D<T>::Vector2D(const Vector2D<T> & _v) : x(_v.x), y(_v.y)
{
};

template<class T> Vector2D<T>::Vector2D(const Vector2D<T> & _from, const Vector2D<T> & _to) : x(_to.x - _from.x), y(_to.y - _from.y)
{
};

template<class T> Vector2D<T>::~Vector2D()
{
};

template<class T> Vector2D<T> Vector2D<T>:: operator+=(const Vector2D<T> &w)
{ 
	x += w.x; y +=w.y; 
	return *this; 
}

template<class T>  Vector2D<T> Vector2D<T>:: operator-=(const Vector2D<T> &w)
{
	x -=w.x; y -=w.y; 
	return *this; 
}

template<class T> T Vector2D<T>::length2(const Vector2D<T> &a)
{ 
	return a.x*a.x + a.y*a.y; 
}

template<class T> T Vector2D<T>::length(const Vector2D<T> &a)
{ 
	return std::sqrt(length2(a)); 
}

template<class T> T Vector2D<T>::length() const
{ 
	return std::sqrt(x*x +y*y); 
}

template<class T> T Vector2D<T>::dist2(const Vector2D<T> &a, const Vector2D<T> &b)
{ 
	return sqr(a.x - b.x) + sqr(a.y - b.y); 
}

template<class T> T Vector2D<T>::dist(const Vector2D<T> &a, const Vector2D<T> &b)
{ 
	return std::sqrt(dist2(a,b)); 
}

template<class T> bool Vector2D<T>::operator==(const Vector2D<T> &a)
{ 
	return x ==a.x && y==a.y; 
}

template<class T> bool Vector2D<T>::operator!=(const Vector2D<T> &a)
{ 
	return x!=a.x || y!=a.y; 
}

template<class T> Vector2D<T> Vector2D<T>:: operator-()
{ 
	
	return Vector2D<T>(-x, -y) ; 
}

template<class T> Vector2D<T> Vector2D<T>:: operator-(const Vector2D<T> &a)
{
	return Vector2D(x-a.x, y-a.y);
}

template<class T> Vector2D<T> Vector2D<T>:: operator+(const Vector2D<T> &a)
{ 
	return Vector2D<T>(x + a.x, y+ a.y);
}

template<class T> Vector2D<T> Vector2D<T>::operator*(const T scalar)
{ 
	return Vector2D<T>(scalar*x, scalar*y); 
}


template<class T> Vector2D<T> Vector2D<T>:: mult(T scalar, const Vector2D<T> &a)
{ 
	return Vector2D<T>(scalar*a.x, scalar*a.y); 
}

template<class T> Vector2D<T> Vector2D<T>:: operator/(T scalar)
{
	return Vector2D<T>(x/scalar, y/scalar); 
}

template<class T> T Vector2D<T>::dot(const Vector2D<T> &a, const Vector2D<T> &b)
{ 
	return a.x*b.x + a.y*b.y; 
}

template<class T> Vector2D<T> & Vector2D<T>::normalize() const
{
    T length(x*x + y*y );
	
	if (length>0.00001)
	{
		T lengthinv = T(1)/sqrt(length);
		x*=lengthinv;
		y*=lengthinv;
	}

    return *this;
  
};

template<class T>  Vector2D<T> Vector2D<T>::perp(const Vector2D<T> &a)
{ 
	return Vector2D<T>(-a.y, a.x); 
}

template<class T>  Vector2D<T> Vector2D<T>::normalize(const Vector2D<T> &a)
{ 
	return a/length(a); 
}

template<class T>  void  Vector2D<T>::normalize() 
{
	T length = std::sqrt(x*x +y*y);
	 x = x/length; y = y/length;
}

//template<class T>  std::ostream  Vector2D<T>::&operator<<(std::ostream &out, const Vector2D<T> &a)
//{ 
//	return out<<a.v[0]<<' '<<a.v[1]; 
//}
//
//template<class T> std::istream  Vector2D<T>::&operator>>(std::istream &in, Vec2<T> &a)
//{ 
//	return in>>a.x>>a.y; 
//}


// common types of vectors ===================================================
//typedef Vector2D<float> Vector2f;
//typedef Vector2D<double> Vector2d;
//typedef Vector2D<int> Vector2i;

};//namespace Math3d