// matrix.h

#pragma once

#include "ray.h"

namespace Math3d {

template<class T> class Matrix3D {
public:
    Matrix3D();
    Matrix3D(const Matrix3D<T> & _m);
	Matrix3D(T* d);
    ~Matrix3D();

    Matrix3D<T> & operator=(const Matrix3D<T> & _m);

    inline T* getData() { return data; };
    inline const T* getData() const { return data; };

    Matrix3D<T> getInv() const;

    Vector3D<T> applyVector(const Vector3D<T> & _v) const;
    Vector3D<T> applyPoint(const Vector3D<T> & _v) const;
    Ray3D<T> apply(const Ray3D<T> & _r) const;
    Matrix3D<T> apply(const Matrix3D<T> & _m) const;
    Vector3D<T> applyTransVector(const Vector3D<T> & _v) const;
    Vector3D<T> applyInvVector(const Vector3D<T> & _v) const;
    Vector3D<T> applyInvPoint(const Vector3D<T> & _v) const;
    Ray3D<T> applyInv(const Ray3D<T> & _r) const;

    Vector3D<T> getA() const;
    Vector3D<T> getB() const;
    Vector3D<T> getC() const;
    Vector3D<T> getI() const;
    Vector3D<T> getJ() const;
    Vector3D<T> getK() const;
    Vector3D<T> getP() const;
    

    void setP(const Vector3D<T> & _p);
    
    void rotateGlobalX(T cosa, T sina);
    void rotateGlobalY(T cosa, T sina);
    void rotateGlobalZ(T cosa, T sina);
    void rotateGlobal(const Vector3D<T> & _v, T cosa, T sina);
    void translateGlobal(const Vector3D<T> & _v);
    void scaleGlobal(const Vector3D<T> & _v);

    void rotateLocalX(T cosa, T sina);
    void rotateLocalY(T cosa, T sina);
    void rotateLocalZ(T cosa, T sina);
    void rotateLocal(const Vector3D<T> & _v, T cosa, T sina);
    void translateLocal(const Vector3D<T> & _v);
    void scaleLocal(const Vector3D<T> & _v);
    
    void rotateLocal(const Vector3D<T> & _from, const Vector3D<T> & _to);
    void rotateGlobal(const Vector3D<T> & _from, const Vector3D<T> & _to);
    
    void lookAt(const Vector3D<T> & _p, const Vector3D<T> & _v, const Vector3D<T> & _u);

    Vector3D<T> getXYZ() const;
	void setXYZ(const Vector3D<T> & _r);

private:
    T* data;
};


template<class T> Matrix3D<T>::Matrix3D() : data(0)
{
    data = new T[16];
    T* ptr(data);
    *(ptr++) = 1;
    *(ptr++) = 0;
    *(ptr++) = 0;
    *(ptr++) = 0;
    
    *(ptr++) = 0;
    *(ptr++) = 1;
    *(ptr++) = 0;
    *(ptr++) = 0;
    
    *(ptr++) = 0;
    *(ptr++) = 0;
    *(ptr++) = 1;
    *(ptr++) = 0;
    
    *(ptr++) = 0;
    *(ptr++) = 0;
    *(ptr++) = 0;
    *ptr = 1;
};

template<class T> Matrix3D<T>::Matrix3D(T* d)
{
	this->data = new T[16];
	T* ptr = this->data;
	for(int i=0; i<16; i++)
	{
		*(ptr++) = d[i];
	}
}

template<class T> Matrix3D<T>::Matrix3D(const Matrix3D<T> & _m) : data(0)
{
    data = new T[16];
    const T* mat(_m.getData());
    T* ptr(data);
    for(int i(16); i--; ) *(ptr++) = *(mat++); 
};

template<class T> Matrix3D<T> & Matrix3D<T>::operator=(const Matrix3D<T> & _m)
{
    const T* mat(_m.getData());
    T* ptr(data);
    for(int i(15); i--; ) *(ptr++) = *(mat++);
    return *this;
};

template<class T> Matrix3D<T>::~Matrix3D()
{
    if(data) delete [] data;
};

template<class T> Matrix3D<T> Matrix3D<T>::getInv() const
{
    Matrix3D<T> matInv;
    T* inv(matInv.getData());

    T det = data[0] * data[5] * data[10]
               + data[1] * data[6] * data[8]
               + data[2] * data[4] * data[9]
               - data[2] * data[5] * data[8]
               - data[1] * data[4] * data[10]
               - data[0] * data[6] * data[9];

    det = 1.0f / det;
    inv[0] =( (data[5] * data[10] - data[9] * data[6]) * det);
    inv[1] =(-(data[1] * data[10] - data[9] * data[2]) * det);
    inv[2] =( (data[1] * data[6] - data[5] * data[2]) * det);

    inv[4] =(-(data[4] * data[10] - data[8] * data[6]) * det);
    inv[5] =( (data[0] * data[10] - data[8] * data[2]) * det);
    inv[6] =(-(data[0] * data[6] - data[4] * data[2]) * det);

    inv[8] =( (data[4] * data[9] - data[8] * data[5]) * det);
    inv[9] =(-(data[0] * data[9] - data[8] * data[1]) * det);
    inv[10]=( (data[0] * data[5] - data[4] * data[1]) * det);

    inv[12] = - ( inv[0]*data[12] + inv[4]*data[13] + inv[8]*data[14] );
    inv[13] = - ( inv[1]*data[12] + inv[5]*data[13] + inv[9]*data[14] );
    inv[14] = - ( inv[2]*data[12] + inv[6]*data[13] + inv[10]*data[14] );

    return matInv;
};

template<class T> Vector3D<T> Matrix3D<T>::applyVector(const Vector3D<T> & _v) const
{
    return Vector3D<T>(data[0]*_v.x + data[4]*_v.y + data[8]*_v.z, data[1]*_v.x + data[5]*_v.y + data[9]*_v.z, data[2]*_v.x + data[6]*_v.y + data[10]*_v.z);
};

template<class T> Vector3D<T> Matrix3D<T>::applyPoint(const Vector3D<T> & _v) const
{
    return Vector3D<T>(data[0]*_v.x + data[4]*_v.y + data[8]*_v.z + data[12], data[1]*_v.x + data[5]*_v.y + data[9]*_v.z + data[13], data[2]*_v.x + data[6]*_v.y + data[10]*_v.z + data[14]);
};

template<class T> Ray3D<T> Matrix3D<T>::apply(const Ray3D<T> & _r) const
{
    return Ray3D<T>( applyPoint(_r.getOrigin()), applyVector(_r.getDirection()) );
};

template<class T> Vector3D<T> Matrix3D<T>::applyInvVector(const Vector3D<T> & _v) const
{
        T det = data[0] * data[5] * data[10]
               + data[1] * data[6] * data[8]
               + data[2] * data[4] * data[9]
               - data[2] * data[5] * data[8]
               - data[1] * data[4] * data[10]
               - data[0] * data[6] * data[9];
               
        det = 1.0f / det;
        Vector3D<T> x( (data[5] * data[10] - data[9] * data[6]) * det,
                       -(data[4] * data[10] - data[8] * data[6]) * det,
                        (data[4] * data[9] - data[8] * data[5]) * det );
        Vector3D<T> y(-(data[1] * data[10] - data[9] * data[2]) * det,
                        (data[0] * data[10] - data[8] * data[2]) * det,
                       -(data[0] * data[9] - data[8] * data[1]) * det );
        Vector3D<T> z( (data[1] * data[6] - data[5] * data[2]) * det,
                       -(data[0] * data[6] - data[4] * data[2]) * det,
                        (data[0] * data[5] - data[4] * data[1]) * det );
                       
        return Vector3D<T>( x*_v, y*_v, z*_v );
};

template<class T> Vector3D<T> Matrix3D<T>::applyInvPoint(const Vector3D<T> & _v) const
{
        T det = data[0] * data[5] * data[10]
               + data[1] * data[6] * data[8]
               + data[2] * data[4] * data[9]
               - data[2] * data[5] * data[8]
               - data[1] * data[4] * data[10]
               - data[0] * data[6] * data[9];
               
        det = 1.0f / det;
        Vector3D<T> x( (data[5] * data[10] - data[9] * data[6]) * det,
                       -(data[4] * data[10] - data[8] * data[6]) * det,
                        (data[4] * data[9] - data[8] * data[5]) * det );
        Vector3D<T> y(-(data[1] * data[10] - data[9] * data[2]) * det,
                        (data[0] * data[10] - data[8] * data[2]) * det,
                       -(data[0] * data[9] - data[8] * data[1]) * det );
        Vector3D<T> z( (data[1] * data[6] - data[5] * data[2]) * det,
                       -(data[0] * data[6] - data[4] * data[2]) * det,
                        (data[0] * data[5] - data[4] * data[1]) * det );
        Vector3D<T> k(_v.x-data[12], _v.y-data[13], _v.z-data[14]);
        return Vector3D<T>( x*k, y*k, z*k );
};

template<class T> Ray3D<T> Matrix3D<T>::applyInv(const Ray3D<T> & _r) const
{
        T det = data[0] * data[5] * data[10]
               + data[1] * data[6] * data[8]
               + data[2] * data[4] * data[9]
               - data[2] * data[5] * data[8]
               - data[1] * data[4] * data[10]
               - data[0] * data[6] * data[9];
               
        det = 1.0f / det;
        Vector3D<T> x( (data[5] * data[10] - data[9] * data[6]) * det,
                       -(data[4] * data[10] - data[8] * data[6]) * det,
                        (data[4] * data[9] - data[8] * data[5]) * det );
        Vector3D<T> y(-(data[1] * data[10] - data[9] * data[2]) * det,
                        (data[0] * data[10] - data[8] * data[2]) * det,
                       -(data[0] * data[9] - data[8] * data[1]) * det );
        Vector3D<T> z( (data[1] * data[6] - data[5] * data[2]) * det,
                       -(data[0] * data[6] - data[4] * data[2]) * det,
                        (data[0] * data[5] - data[4] * data[1]) * det );
        
        Vector3D<T> k(_r.getOrigin().x-data[12], _r.getOrigin().y-data[13], _r.getOrigin().z-data[14]);
               
        return Ray3D<T> (Vector3D<T>( x*k, y*k, z*k ), Vector3D<T>( x*_r.getDirection(), y*_r.getDirection(), z*_r.getDirection() ));
};

template<class T> Matrix3D<T> Matrix3D<T>::apply(const Matrix3D<T> & _m) const
{
    Matrix3D<T> matrix;
    T* res(matrix.getData());
    const T* mat(_m.getData());
    
    *(res++) = data[0]*mat[0] + data[4]*mat[1] + data[8]*mat[2];
    *(res++) = data[1]*mat[0] + data[5]*mat[1] + data[9]*mat[2];
    *(res++) = data[2]*mat[0] + data[6]*mat[1] + data[10]*mat[2];
    res++;
    
    *(res++) = data[0]*mat[4] + data[4]*mat[5] + data[8]*mat[6];
    *(res++) = data[1]*mat[4] + data[5]*mat[5] + data[9]*mat[6];
    *(res++) = data[2]*mat[4] + data[6]*mat[5] + data[10]*mat[6];
    res++;
    
    *(res++) = data[0]*mat[8] + data[4]*mat[9] + data[8]*mat[10];
    *(res++) = data[1]*mat[8] + data[5]*mat[9] + data[9]*mat[10];
    *(res++) = data[2]*mat[8] + data[6]*mat[9] + data[10]*mat[10];
    res++;
    
    *(res++) = data[0]*mat[12] + data[4]*mat[13] + data[8]*mat[14] + data[12];
    *(res++) = data[1]*mat[12] + data[5]*mat[13] + data[9]*mat[14] + data[13];
    *res     = data[2]*mat[12] + data[6]*mat[13] + data[10]*mat[14] + data[14];
    
    return matrix;
};

template<class T> Vector3D<T> Matrix3D<T>::applyTransVector(const Vector3D<T> & _v) const
{
    return Vector3D<T>(data[0]*_v.x+data[1]*_v.y+data[2]*_v.z, data[4]*_v.x+data[5]*_v.y+data[6]*_v.z, data[8]*_v.x+data[9]*_v.y+data[10]*_v.z);
};


template<class T> Vector3D<T> Matrix3D<T>::getA() const
{
    return Vector3D<T>(data[0], data[4], data[8]);
};

template<class T> Vector3D<T> Matrix3D<T>::getB() const
{
    return Vector3D<T>(data[1], data[5], data[9]);
};

template<class T> Vector3D<T> Matrix3D<T>::getC() const
{
    return Vector3D<T>(data[2], data[6], data[10]);
};

template<class T> Vector3D<T> Matrix3D<T>::getI() const
{
    return Vector3D<T>(data[0], data[1], data[2]);
};

template<class T> Vector3D<T> Matrix3D<T>::getJ() const
{
    return Vector3D<T>(data[4], data[5], data[6]);
};

template<class T> Vector3D<T> Matrix3D<T>::getK() const
{
    return Vector3D<T>(data[8], data[9], data[10]);
};

template<class T> Vector3D<T> Matrix3D<T>::getP() const
{
    return Vector3D<T>(data[12], data[13], data[14]);
};

template<class T> void Matrix3D<T>::setP(const Vector3D<T> & _p)
{
    data[12] = _p.x;
    data[13] = _p.y;
    data[14] = _p.z;
};

template<class T> void Matrix3D<T>::rotateGlobalX(T cosa, T sina)
{
    T b,c;
    
    b=data[1];
    c=data[2];
    data[1]=cosa*b-sina*c;
    data[2]=sina*b+cosa*c;

    b=data[5];
    c=data[6];
    data[5]=cosa*b-sina*c;
    data[6]=sina*b+cosa*c;

    b=data[9];
    c=data[10];
    data[9]=cosa*b-sina*c;
    data[10]=sina*b+cosa*c;
};

template<class T> void Matrix3D<T>::rotateGlobalY(T cosa, T sina)
{
    T a,c;
    
    a=data[0];
    c=data[2];
    data[0]=cosa*a+sina*c;
    data[2]=cosa*c-sina*a;

    a=data[4];
    c=data[6];
    data[4]=cosa*a+sina*c;
    data[6]=cosa*c-sina*a;

    a=data[8];
    c=data[10];
    data[8]=cosa*a+sina*c;
    data[10]=cosa*c-sina*a;
};

template<class T> void Matrix3D<T>::rotateGlobalZ(T cosa, T sina)
{
    T a,b;
    
    a=data[0];
    b=data[1];
    data[0]=cosa*a-sina*b;
    data[1]=sina*a+cosa*b;

    a=data[4];
    b=data[5];
    data[4]=cosa*a-sina*b;
    data[5]=sina*a+cosa*b;

    a=data[8];
    b=data[9];
    data[8]=cosa*a-sina*b;
    data[9]=sina*a+cosa*b;
};

template<class T> void Matrix3D<T>::rotateGlobal(const Vector3D<T> & _v, T cosa, T sina)
{
    T oneMcos(1.0f - cosa);
    T ix( cosa +  oneMcos*_v.x*_v.x );
    T iy( oneMcos*_v.x*_v.y + sina*_v.z );
    T iz( oneMcos*_v.x*_v.z - sina*_v.y);
    T jx( oneMcos*_v.x*_v.y - sina*_v.z );
    T jy( cosa +  oneMcos*_v.y*_v.y );
    T jz( oneMcos*_v.y*_v.z + sina*_v.x);
    T kx( oneMcos*_v.x*_v.z + sina*_v.y );
    T ky( oneMcos*_v.y*_v.z - sina*_v.x );
    T kz( cosa + oneMcos*_v.z*_v.z);

    T a,b,c;
    T* ptr(data);
    a=*ptr;
    b=*(ptr+1);
    c=*(ptr+2);
    *(ptr++) = ix*a + jx*b + kx*c;
    *(ptr++) = iy*a + jy*b + ky*c;
    *(ptr++) = iz*a + jz*b + kz*c;
    ptr++;

    a=*ptr;
    b=*(ptr+1);
    c=*(ptr+2);
    *(ptr++) = ix*a + jx*b + kx*c;
    *(ptr++) = iy*a + jy*b + ky*c;
    *(ptr++) = iz*a + jz*b + kz*c;
    ptr++;

    a=*ptr;
    b=*(ptr+1);
    c=*(ptr+2);
    *(ptr++) = ix*a + jx*b + kx*c;
    *(ptr++) = iy*a + jy*b + ky*c;
    *(ptr++) = iz*a + jz*b + kz*c;
};

template<class T> void Matrix3D<T>::translateGlobal(const Vector3D<T> & _v)
{
    data[12]+=_v.x;
    data[13]+=_v.y;
    data[14]+=_v.z;
};

template<class T> void Matrix3D<T>::scaleGlobal(const Vector3D<T> & _v)
{
    T* ptr(data);
    *(ptr++) *= _v.x;
    *(ptr++) *= _v.y;
    *(ptr++) *= _v.z;
    ptr++;

    *(ptr++) *= _v.x;
    *(ptr++) *= _v.y;
    *(ptr++) *= _v.z;
    ptr++;

    *(ptr++) *= _v.x;
    *(ptr++) *= _v.y;
    *ptr *= _v.z;
};

template<class T> void Matrix3D<T>::rotateLocalX(T cosa, T sina)
{
    T* ptr(data+4);
    T b;

    b=*ptr;
    *ptr = cosa*b + sina*(*(ptr+4));
    *(ptr+4) = cosa*(*(ptr+4)) - sina*b;
    ptr++;

    b=*ptr;
    *ptr = cosa*b + sina*(*(ptr+4));
    *(ptr+4) = cosa*(*(ptr+4)) - sina*b;
    ptr++;

    b=*ptr;
    *ptr = cosa*b + sina*(*(ptr+4));
    *(ptr+4) = cosa*(*(ptr+4)) - sina*b;
};

template<class T> void Matrix3D<T>::rotateLocalY(T cosa, T sina)
{
    T* ptr(data);
    T b;

    b=*ptr;
    *ptr = cosa*b - sina*(*(ptr+8));
    *(ptr+8) = sina*b + cosa*(*(ptr+8));
    ptr++;

    b=*ptr;
    *ptr = cosa*b - sina*(*(ptr+8));
    *(ptr+8) = sina*b + cosa*(*(ptr+8));
    ptr++;

    b=*ptr;
    *ptr = cosa*b - sina*(*(ptr+8));
    *(ptr+8) = sina*b + cosa*(*(ptr+8));
};

template<class T> void Matrix3D<T>::rotateLocalZ(T cosa, T sina)
{
    T* ptr(data);
    T b;

    b=*ptr;
    *ptr = cosa*b + sina*(*(ptr+4));
    *(ptr+4) = cosa*(*(ptr+4)) - sina*b;
    ptr++;

    b=*ptr;
    *ptr = cosa*b + sina*(*(ptr+4));
    *(ptr+4) = cosa*(*(ptr+4)) - sina*b;
    ptr++;

    b=*ptr;
    *ptr = cosa*b + sina*(*(ptr+4));
    *(ptr+4) = cosa*(*(ptr+4)) - sina*b;
};

template<class T> void Matrix3D<T>::rotateLocal(const Vector3D<T> & _v, T cosa, T sina)
{
    T oneMcos(1.0f - cosa);
    T ix( cosa +  oneMcos*_v.x*_v.x );
    T iy( oneMcos*_v.x*_v.y + sina*_v.z );
    T iz( oneMcos*_v.x*_v.z - sina*_v.y);
    T jx( oneMcos*_v.x*_v.y - sina*_v.z );
    T jy( cosa +  oneMcos*_v.y*_v.y );
    T jz( oneMcos*_v.y*_v.z + sina*_v.x);
    T kx( oneMcos*_v.x*_v.z + sina*_v.y );
    T ky( oneMcos*_v.y*_v.z - sina*_v.x );
    T kz( cosa + oneMcos*_v.z*_v.z);

    T a,b,c;
    T* ptr(data);
    
    a=*ptr;
    b=*(ptr+4);
    c=*(ptr+8);
    *ptr     = a*ix + b*iy + c*iz;
    *(ptr+4) = a*jx + b*jy + c*jz;
    *(ptr+8) = a*kx + b*ky + c*kz;
    ptr++;

    a=*ptr;
    b=*(ptr+4);
    c=*(ptr+8);
    *ptr     = a*ix + b*iy + c*iz;
    *(ptr+4) = a*jx + b*jy + c*jz;
    *(ptr+8) = a*kx + b*ky + c*kz;
    ptr++;

    a=*ptr;
    b=*(ptr+4);
    c=*(ptr+8);
    *ptr     = a*ix + b*iy + c*iz;
    *(ptr+4) = a*jx + b*jy + c*jz;
    *(ptr+8) = a*kx + b*ky + c*kz;
};

template<class T> void Matrix3D<T>::translateLocal(const Vector3D<T> & _v)
{
    data[12] += data[0] * _v.x + data[4] * _v.y + data[8] * _v.z;
    data[13] += data[1] * _v.x + data[5] * _v.y + data[9] * _v.z;
    data[14] += data[2] * _v.x + data[6] * _v.y + data[10] * _v.z;
};

template<class T> void Matrix3D<T>::scaleLocal(const Vector3D<T> & _v)
{
    T* ptr(data);
    *(ptr++) *= _v.x;
    *(ptr++) *= _v.x;
    *(ptr++) *= _v.x;
    ptr++;

    *(ptr++) *= _v.y;
    *(ptr++) *= _v.y;
    *(ptr++) *= _v.y;
    ptr++;

    *(ptr++) *= _v.z;
    *(ptr++) *= _v.z;
    *ptr *= _v.z;
};

template<class T> void Matrix3D<T>::rotateLocal(const Vector3D<T> & _from, const Vector3D<T> & _to)
{
    Vector3D<T> from(_from.getUnit());
    Vector3D<T> to(_to.getUnit());
    
    Vector3D<T> axe(from^to);
    double sina(axe.length());
    axe/=sina;
    double cosa(from*to);
    
    rotateLocal(axe, cosa, sina);
};

template<class T> void Matrix3D<T>::rotateGlobal(const Vector3D<T> & _from, const Vector3D<T> & _to)
{
    Vector3D<T> from(_from.getUnit());
    Vector3D<T> to(_to.getUnit());
    
    Vector3D<T> axe(from^to);
    double sina(axe.length());
    axe/=sina;
    double cosa(from*to);
    
    rotateGlobal(axe, cosa, sina);
};

template<class T> void Matrix3D<T>::lookAt(const Vector3D<T> & _p, const Vector3D<T> & _v, const Vector3D<T> & _u)
{
    Vector3D<T> k((_p - _v).normalize());
    Vector3D<T> i((_u^k).normalize());
    Vector3D<T> j(k^i);
    
    T* ptr(data);
    *(ptr++) = i.x;
    *(ptr++) = j.x;
    *(ptr++) = k.x;
    ptr++;

    *(ptr++) = i.y;
    *(ptr++) = j.y;
    *(ptr++) = k.y;
    ptr++;

    *(ptr++) = i.z;
    *(ptr++) = i.z;
    *(ptr++) = i.z;
    ptr++;
    
    *(ptr++) = -(i*_p);
    *(ptr++) = -(j*_p);
    *ptr     = -(k*_p);  
};

template<class T> Vector3D<T> Matrix3D<T>::getXYZ() const
{
    Vector3D<T> vector;

    vector.x = atan2(data[6], data[10]);
    vector.z = atan2(data[1], data[0]);
    vector.y = atan2(-data[2], data[6]/sin(vector.x) );

    return vector;
}

template<class T> void Matrix3D<T>::setXYZ(const Vector3D<T> & _r)
{
	Dvector c( cos(_r.x), cos(_r.y), cos(_r.z) );
	Dvector s( sin(_r.x), sin(_r.y), sin(_r.z) );

	T* ptr(data);
	*ptr++ = c.y * c.z;
	*ptr++ = c.y * s.z;
	*ptr++ = -s.z;
	ptr++;
	*ptr++ = -s.z*c.x + c.z*s.y*s.x;
	*ptr++ = c.z*c.x + s.z*s.y*s.x;
	*ptr++ = c.y*s.x;
	ptr++;
	*ptr++ = s.z*s.x + c.z*s.y*c.x;
	*ptr++ = c.x*s.z*s.y - c.z*s.x;
	*ptr   = c.x*c.y;
}

};
