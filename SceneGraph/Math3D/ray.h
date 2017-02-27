// ray.h

#pragma once

#include "vector.h"

  
namespace Math3d {

template<class T> class Ray3D {
public:
    Ray3D(Vector3D<T> _o, Vector3D<T> _d);
    ~Ray3D();

    inline Vector3D<T> & getOrigin() { return origin; };
    inline const Vector3D<T> & getOrigin() const { return origin; };

    inline Vector3D<T> & getDirection() { return direction; };
    inline const Vector3D<T> & getDirection() const { return direction; };

    Ray3D<T> getUnit() const;
    Ray3D<T> & normalize();

    Vector3D<T> get(T _d) const;
    Vector3D<T> proj(const Vector3D<T> & _v) const;
    
    T getDistance(const Vector3D<T> & _v) const;
    T getDistance2(const Vector3D<T> & _v) const;
private:
    Vector3D<T> origin;
    Vector3D<T> direction;
};



template<class T> Ray3D<T>::Ray3D(Vector3D<T> _o, Vector3D<T> _d) : origin(_o), direction(_d)
{
};

template<class T> Ray3D<T>::~Ray3D()
{
};

template<class T> Ray3D<T> Ray3D<T>::getUnit() const
{
    return Ray3D<T>(origin, direction.getUnit());
};

template<class T> Ray3D<T> & Ray3D<T>::normalize()
{
    direction.normalize();
};

template<class T> Vector3D<T> Ray3D<T>::get(T _d) const
{
    return origin+(direction*_d);
};

template<class T> T Ray3D<T>::getDistance(const Vector3D<T> & _v) const
{
    Vector3D<T> dist(origin, _v);
    Vector3D<T> unit(direction.getUnit());
    dist -= (unit*= unit*dist);
    return dist.length();
};

template<class T> T Ray3D<T>::getDistance2(const Vector3D<T> & _v) const
{
    Vector3D<T> dist(origin, _v);
    Vector3D<T> unit(direction.getUnit());
    dist -= (unit *= (unit*dist));
    return dist.length2();
};

template<class T> Vector3D<T> Ray3D<T>::proj(const Vector3D<T> & _v) const
{
    Vector3D<T> dist(origin, _v);
    Vector3D<T> unit(direction.getUnit());
    return origin + (unit*= (unit*dist));
};

};
