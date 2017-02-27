// vector.h

#pragma once

#include <math.h>
#include <cmath>
#include <limits>
#include <iostream>

#include "vector.h"

namespace Math3d
{
	
	template<class T> class Vector4D
	{
	public:
		Vector4D(T _x = 0, T _y = 0, T _z = 0, T _w = 0);
		Vector4D(const Vector4D<T> & _v);
		Vector4D(const Vector4D<T> & _from, const Vector4D<T> & _to);
		~Vector4D();

		Vector3D<T> xyz() const;

		void set(T _x, T _y, T _z, T _w);
	    
		Vector4D<T> operator+(const Vector4D<T> & _v) const;
		Vector4D<T> operator-(const Vector4D<T> & _v) const;
		T operator*(const Vector4D<T> & _v) const;

		Vector4D<T> mult(const Vector4D<T> & _v) const;
		Vector4D<T> operator*(T _d) const;
		Vector4D<T> operator/(T _d) const;

		Vector4D<T> & operator=(const Vector4D<T> & _v);
		Vector4D<T> & operator+=(const Vector4D<T> & _v);
		Vector4D<T> & operator-=(const Vector4D<T> & _v);
		Vector4D<T> & operator*=(T _d);
		Vector4D<T> & operator/=(T _d);
		Vector4D<T> operator-();

		T length() const;
		T length2() const;
		T distance(const Vector4D<T> & _v) const;
		T distance2(const Vector4D<T> & _v) const;

		void normalize();
	    

		T x, y, z, w;
	};

	template<class T> Vector4D<T>::Vector4D(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w)
	{
	}

	template<class T> Vector4D<T>::Vector4D(const Vector4D<T> & _v) : x(_v.x), y(_v.y), z(_v.z), w(_v.w)
	{
	}

	template<class T> Vector4D<T>::Vector4D(const Vector4D<T> & _from, const Vector4D<T> & _to) : x(_to.x - _from.x), y(_to.y - _from.y), z(_to.z - _from.z), w(_to.w - _from.w)
	{
	}

	template<class T> Vector4D<T>::~Vector4D()
	{
	}
	template<class T> Vector3D<T> Vector4D<T>::xyz() const
	{
		return Vector3D<T>(x,y,z);
	}

	template<class T> void Vector4D<T>::set(T _x, T _y, T _z, T _w)
	{
		x=_x;
		y=_y;
		z=_z;
		w=_w;
	}

	template<class T> Vector4D<T> Vector4D<T>::operator+(const Vector4D<T> & _v) const
	{
		return Vector4D(x+_v.x, y+_v.y, z+_v.z, w+_v.w);
	}
	template<class T> Vector4D<T> Vector4D<T>::mult(const Vector4D<T> & _v) const
	{
		return Vector4D(x*_v.x, y*_v.y, z*_v.z, w*_v.w);
	}
	template<class T> Vector4D<T> Vector4D<T>::operator-(const Vector4D<T> & _v) const
	{
		return Vector4D(x-_v.x, y-_v.y, z-_v.z, w-_v.w);
	}

	template<class T> T Vector4D<T>::operator*(const Vector4D<T> & _v) const
	{
		return x*_v.x + y*_v.y + z*_v.z + w*_v.w;
	};


	template<class T> Vector4D<T> Vector4D<T>::operator*(T _d) const
	{
		return Vector4D<T>(x*_d, y*_d, z*_d, w+_d);
	}

	template<class T> Vector4D<T> Vector4D<T>::operator/(T _d) const
	{
		return Vector4D<T>(x/_d, y/_d, z/_d, w/_d);
	}

	template<class T> Vector4D<T> & Vector4D<T>::operator=(const Vector4D<T> & _v)
	{
		x=_v.x;
		y=_v.y;
		z=_v.z;
		w=_v.w;
		return *this;
	}

	template<class T> Vector4D<T> & Vector4D<T>::operator+=(const Vector4D<T> & _v)
	{
		x+=_v.x;
		y+=_v.y;
		z+=_v.z;
		w+=_v.w;
		return *this;
	}

	template<class T> Vector4D<T> & Vector4D<T>::operator-=(const Vector4D<T> & _v)
	{
		x-=_v.x;
		y-=_v.y;
		z-=_v.z;
		w-=_v.w;
		return *this;
	}

	template<class T> Vector4D<T> & Vector4D<T>::operator*=(T _d)
	{
		x*=_d;
		y*=_d;
		z*=_d;
		w*=d;
		return *this;
	}

	template<class T> Vector4D<T> & Vector4D<T>::operator/=(T _d)
	{
		x/=_d;
		y/=_d;
		z/=_d;
		w/=_d;
		return *this;
	}

	template<class T> Vector4D<T> Vector4D<T>::operator-()
	{
		return Vector4D<T>(-x, -y, -z, -w);
	}


	template<class T> T Vector4D<T>::length() const
	{
		return sqrt(x*x + y*y + z*z + w*w);
	}

	template<class T> T Vector4D<T>::length2() const
	{
		return x*x + y*y + z*z +w*w;
	}

	template<class T> T Vector4D<T>::distance(const Vector4D<T> & _v) const
	{
		T tx(_v.x-x);
		T ty(_v.y-y);
		T tz(_v.z-z);
		T tw(_v.w-w);
		return sqrt(tx*tx + ty*ty + tz*tz + tw*tw);
	}

	template<class T> T Vector4D<T>::distance2(const Vector4D<T> & _v) const
	{
		T tx(_v.x-x);
		T ty(_v.y-y);
		T tz(_v.z-z);
		T tw(_v.w-w);
		return tx*tx + ty*ty + tz*tz + tw*tw;
	}

	template<class T> void Vector4D<T>::normalize()
	{
		T l = sqrt(x*x + y*y + z*z);
		x /= l; y/=l; z/=l;
	}
	
};

