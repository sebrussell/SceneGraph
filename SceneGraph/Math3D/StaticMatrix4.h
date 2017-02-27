#pragma once
#include "vector4.h"
#include <limits>

namespace Math3d
{
	template<class T> 
	class StaticMatrix4
	{
	private:
		T data[16];
	public:
		StaticMatrix4(void);
		StaticMatrix4(T* data);
		StaticMatrix4(const Math3d::Vector4D<T>& c1, const Math3d::Vector4D<T>& c2, const Math3d::Vector4D<T>& c3, const Math3d::Vector4D<T>& c4);
		~StaticMatrix4(void);

		void setRow(const int row, const Math3d::Vector4D<T>& v);
		void setColumn(const int column, const Math3d::Vector4D<T>& v);
		Math3d::Vector4D<T> getRow(const int row) const;
		Math3d::Vector4D<T> getColumn(const int column) const;

		void negateRow(const int row);
		void negateColumn(const int column);

		inline const T* getData() const;

		inline T get(const int row, const int column) const;
		inline void set(const int row, const int column, const T v);
		inline void set(const int offset, const T v);

		static StaticMatrix4 identity();

		// Transforms
		static StaticMatrix4 rotationX(const T angle);
		static StaticMatrix4 rotationY(const T angle);
		static StaticMatrix4 rotationZ(const T angle);
		static StaticMatrix4 rotation(const T angle, const Math3d::Vector3D<T>& axis);
		static StaticMatrix4 scale(const Math3d::Vector3D<T>& size);
		static StaticMatrix4 translation(const Math3d::Vector3D<T>& position);
		static StaticMatrix4 perspProj(const T fov, const T aspect, const T near, const T far);
		static void look_at(const Math3d::Vector3D<T>& position, const Math3d::Vector3D<T>& target, const Math3d::Vector3D<T>& up, StaticMatrix4<T>& out_lookat);
		Math3d::Vector3D<T> get_rotation() const;

		// Inverse
		T getDeterminant() const;
		StaticMatrix4 getInverse() const;
		void getInverse(StaticMatrix4& out_inverse) const;

		StaticMatrix4<T> operator *(const StaticMatrix4<T>& mm);

	};

	//
	template<class T> Math3d::Vector4D<T> operator*(const StaticMatrix4<T>& m, const Math3d::Vector4D<T>& v);
	template<class T> Math3d::Vector4D<T> operator*(const Math3d::Vector4D<T>& v, const StaticMatrix4<T>& m);

	template<class T>
	StaticMatrix4<T>::StaticMatrix4(void)
	{
	}
	template<class T>
	StaticMatrix4<T>::StaticMatrix4(T* _data)
	{
		memcpy(this->data, _data, 16*sizeof(T));
	}

	template<class T>
	StaticMatrix4<T>::StaticMatrix4(const Math3d::Vector4D<T>& c1, const Math3d::Vector4D<T>& c2, const Math3d::Vector4D<T>& c3, const Math3d::Vector4D<T>& c4)
	{
		this->setColumn( 0, c1 );
		this->setColumn( 1, c2 );
		this->setColumn( 2, c3 );
		this->setColumn( 3, c4 );
	}
	template<class T>
	StaticMatrix4<T>::~StaticMatrix4(void)
	{
	}

	template<class T>
	void StaticMatrix4<T>::setRow(const int row, const Math3d::Vector4D<T>& v)
	{
		this->set(row,0, v.x);
		this->set(row,1, v.y);
		this->set(row,2, v.z);
		this->set(row,3, v.w);
	}
	template<class T>
	void StaticMatrix4<T>::setColumn(const int column, const Math3d::Vector4D<T>& v)
	{
		this->set(0,column, v.x);
		this->set(1,column, v.y);
		this->set(2,column, v.z);
		this->set(3,column, v.w);
	}
	template<class T>
	Math3d::Vector4D<T> StaticMatrix4<T>::getRow(const int row) const
	{
		return Math3d::Vector4D<T>(this->get(row,0), this->get(row,1), this->get(row,2), this->get(row,3));
	}
	template<class T>
	Math3d::Vector4D<T> StaticMatrix4<T>::getColumn(const int column) const
	{
		return Math3d::Vector4D<T>(this->get(0,column), this->get(1,column), this->get(2,column), this->get(3,column));
	}

	template<class T>
	void StaticMatrix4<T>::negateRow(const int row)
	{
		T* ptr = this->data+row*4;
		*ptr = -*ptr; ptr+=4;
		*ptr = -*ptr; ptr+=4;
		*ptr = -*ptr; ptr+=4;
		*ptr = -*ptr; ptr+=4;
	}
	template<class T>
	void StaticMatrix4<T>::negateColumn(const int column)
	{
		T* ptr = this->data+column*4;
		*ptr = -*ptr; ptr++;
		*ptr = -*ptr; ptr++;
		*ptr = -*ptr; ptr++;
		*ptr = -*ptr; ptr++;
	}

	template<class T>
	inline const T* StaticMatrix4<T>::getData() const
	{
		return this->data;
	}


	template<class T>
	inline T StaticMatrix4<T>::get(const int row, const int column) const
	{
		return this->data[row+column*4];
	}
	template<class T>
	inline void StaticMatrix4<T>::set(const int row, const int column, const T v)
	{
		this->data[row+column*4] = v;
	}
	template<class T>
	inline void StaticMatrix4<T>::set(const int offset, const T v)
	{
		this->data[offset] = v;
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::identity()
	{
		StaticMatrix4<T> m;
		
		m.set(0,0,1); m.set(1,0,0); m.set(2,0,0); m.set(3,0,0);
		m.set(0,1,0); m.set(1,1,1); m.set(2,1,0); m.set(3,1,0);
		m.set(0,2,0); m.set(1,2,0); m.set(2,2,1); m.set(3,2,0); 
		m.set(0,3,0); m.set(1,3,0); m.set(2,3,0); m.set(3,3,1); 
		
		return m;
	}

	// Transforms
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::rotationX(const T angle)
	{
		T rad = angle*3.141592f/180.f;
		T c = cos(rad);
		T s = sin(rad);

		Math3d::Vector4D<T> r1(1,0,0,0);
		Math3d::Vector4D<T> r2(0,c,-s,0);
		Math3d::Vector4D<T> r3(0,s,c,0);
		Math3d::Vector4D<T> r4(0,0,0,1);
		return StaticMatrix4(r1, r2, r3, r4);
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::rotationY(const T angle)
	{
		T rad = angle*3.141592f/180.f;
		T c = cos(rad);
		T s = sin(rad);

		Math3d::Vector4D<T> r1(c,0,s,0);
		Math3d::Vector4D<T> r2(0,1,0,0);
		Math3d::Vector4D<T> r3(-s,0,c,0);
		Math3d::Vector4D<T> r4(0,0,0,1);
		return StaticMatrix4(r1, r2, r3, r4);
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::rotationZ(const T angle)
	{
		T rad = angle*3.141592f/180.f;
		T c = cos(rad);
		T s = sin(rad);
		Math3d::Vector4D<T> r1(c,-s,0,0);
		Math3d::Vector4D<T> r2(s,c,0,0);
		Math3d::Vector4D<T> r3(0,0,1,0);
		Math3d::Vector4D<T> r4(0,0,0,1);
		return StaticMatrix4(r1, r2, r3, r4);
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::rotation(const T angle, const Math3d::Vector3D<T>& axis)
	{
		T rad = angle*3.141592f/180.f;
		T c = cos(rad);
		T s = sin(rad);
		T t = 1-c;
		Math3d::Vector4D<T> r1(t*axis.x*axis.x + c,			t*axis.x*axis.y - s*axis.z,		t*axis.x*axis.z + s*axis.y, 0);
		Math3d::Vector4D<T> r2(t*axis.x*axis.y + s*axis.z,	t*axis.y*axis.y + c,			t*axis.y*axis.z - s*axis.x, 0);
		Math3d::Vector4D<T> r3(t*axis.x*axis.z - s*axis.y,	t*axis.y*axis.z - s*axis.x,		t*axis.z*axis.z + c, 0);
		Math3d::Vector4D<T> r4(0,0,0,1);
		return StaticMatrix4(r1, r2, r3, r4);
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::scale(const Math3d::Vector3D<T>& size)
	{
		Math3d::Vector4D<T> r1(size.x,0,0,0);
		Math3d::Vector4D<T> r2(0,size.y,0,0);
		Math3d::Vector4D<T> r3(0,0,size.z,0);
		Math3d::Vector4D<T> r4(0,0,0,1);
		return StaticMatrix4(r1, r2, r3, r4);
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::translation(const Math3d::Vector3D<T>& position)
	{
		Math3d::Vector4D<T> r1(1,0,0,0);
		Math3d::Vector4D<T> r2(0,1,0,0);
		Math3d::Vector4D<T> r3(0,0,1,0);
		Math3d::Vector4D<T> r4(position.x,position.y,position.z,1);
		return StaticMatrix4(r1, r2, r3, r4);
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::perspProj(const T fov, const T aspect, const T near, const T far)
	{
		//const T t = tanf( fov * 3.142f / 360.f );

		const T fd = 1.f/tanf( fov * 3.142f / 360.f );
		Math3d::Vector4D<T> c1(fd/aspect,	0,	0,						0);
		Math3d::Vector4D<T> c2(0,			fd,	0,						0);
		Math3d::Vector4D<T> c3(0,			0,	-(far+near)/(far-near),	-1);
		Math3d::Vector4D<T> c4(0,			0,	-(2*far*near)/(far-near),0);

		/*Math3d::Vector4D<T> c1(fd/aspect,	0,	0,						0);
		Math3d::Vector4D<T> c2(0,			fd,	0,						0);
		Math3d::Vector4D<T> c3(0,			0,	-(far+near)/(far-near),	-(2*far*near)/(far-near));
		Math3d::Vector4D<T> c4(0,			0,	-1,0);*/

		return StaticMatrix4(c1,c2,c3,c4);
	}

	// Inverse
	template<class T>
	T StaticMatrix4<T>::getDeterminant() const
	{
		return
			data[12]*data[9]*data[6]*data[3] - data[8]*data[13]*data[6]*data[3] - data[12]*data[5]*data[10]*data[3] + data[4]*data[13]*data[10]*data[3] +
			data[8]*data[5]*data[14]*data[3] - data[4]*data[9]*data[14]*data[3] - data[12]*data[9]*data[2]*data[7] + data[8]*data[13]*data[2]*data[7] +
			data[12]*data[1]*data[10]*data[7] - data[0]*data[13]*data[10]*data[7] - data[8]*data[1]*data[14]*data[7] + data[0]*data[9]*data[14]*data[7] +
			data[12]*data[5]*data[2]*data[11] - data[4]*data[13]*data[2]*data[11] - data[12]*data[1]*data[6]*data[11] + data[0]*data[13]*data[6]*data[11] +
			data[4]*data[1]*data[14]*data[11] - data[0]*data[5]*data[14]*data[11] - data[8]*data[5]*data[2]*data[15] + data[4]*data[9]*data[2]*data[15] +
			data[8]*data[1]*data[6]*data[15] - data[0]*data[9]*data[6]*data[15] - data[4]*data[1]*data[10]*data[15] + data[0]*data[5]*data[10]*data[15];
	}
	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::getInverse() const
	{
		StaticMatrix4 i;
		T x = this->getDeterminant();
		i.set(0, (-data[13]*data[10]*data[7] + data[9]*data[14]*data[7] + data[13]*data[6]*data[11] - data[5]*data[14]*data[11] - data[9]*data[6]*data[15] + data[5]*data[10]*data[15])/x);
		i.set(4, ( data[12]*data[10]*data[7] - data[8]*data[14]*data[7] - data[12]*data[6]*data[11] + data[4]*data[14]*data[11] + data[8]*data[6]*data[15] - data[4]*data[10]*data[15])/x);
		i.set(8, (-data[12]*data[9]*data[7] + data[8]*data[13]*data[7] + data[12]*data[5]*data[11] - data[4]*data[13]*data[11] - data[8]*data[5]*data[15] + data[4]*data[9]*data[15])/x);
		i.set(12, (data[12]*data[9]*data[6] - data[8]*data[13]*data[6] - data[12]*data[5]*data[10] + data[4]*data[13]*data[10] + data[8]*data[5]*data[14] - data[4]*data[9]*data[14])/x);
		i.set(1, (data[13]*data[10]*data[3] - data[9]*data[14]*data[3] - data[13]*data[2]*data[11] + data[1]*data[14]*data[11] + data[9]*data[2]*data[15] - data[1]*data[10]*data[15])/x);
		i.set(5, (-data[12]*data[10]*data[3] + data[8]*data[14]*data[3] + data[12]*data[2]*data[11] - data[0]*data[14]*data[11] - data[8]*data[2]*data[15] + data[0]*data[10]*data[15])/x);
		i.set(9, (data[12]*data[9]*data[3] - data[8]*data[13]*data[3] - data[12]*data[1]*data[11] + data[0]*data[13]*data[11] + data[8]*data[1]*data[15] - data[0]*data[9]*data[15])/x);
		i.set(13, (-data[12]*data[9]*data[2] + data[8]*data[13]*data[2] + data[12]*data[1]*data[10] - data[0]*data[13]*data[10] - data[8]*data[1]*data[14] + data[0]*data[9]*data[14])/x);
		i.set(2, (-data[13]*data[6]*data[3] + data[5]*data[14]*data[3] + data[13]*data[2]*data[7] - data[1]*data[14]*data[7] - data[5]*data[2]*data[15] + data[1]*data[6]*data[15])/x);
		i.set(6, ( data[12]*data[6]*data[3] - data[4]*data[14]*data[3] - data[12]*data[2]*data[7] + data[0]*data[14]*data[7] + data[4]*data[2]*data[15] - data[0]*data[6]*data[15])/x);
		i.set(10, (-data[12]*data[5]*data[3] + data[4]*data[13]*data[3] + data[12]*data[1]*data[7] - data[0]*data[13]*data[7] - data[4]*data[1]*data[15] + data[0]*data[5]*data[15])/x);
		i.set(14, (data[12]*data[5]*data[2] - data[4]*data[13]*data[2] - data[12]*data[1]*data[6] + data[0]*data[13]*data[6] + data[4]*data[1]*data[14] - data[0]*data[5]*data[14])/x);
		i.set(3, (data[9]* data[6]*data[3] - data[5]*data[10]*data[3] - data[9]* data[2]*data[7] + data[1]*data[10]*data[7] + data[5]*data[2]*data[11] - data[1]*data[6]*data[11])/x);
		i.set(7, (-data[8]* data[6]*data[3] + data[4]*data[10]*data[3] + data[8]* data[2]*data[7] - data[0]*data[10]*data[7] - data[4]*data[2]*data[11] + data[0]*data[6]*data[11])/x);
		i.set(11, ( data[8]*data[5]*data[3] - data[4]*data[9]*data[3] - data[8]* data[1]*data[7] + data[0]*data[9]*data[7] + data[4]*data[1]*data[11] - data[0]*data[5]*data[11])/x);
		i.set(15, (-data[8]*data[5]*data[2] + data[4]*data[9]*data[2] + data[8]*data[1]*data[6] - data[0]*data[9]*data[6] - data[4]*data[1]*data[10] + data[0]*data[5]* data[10])/x);
		return i;
	}
	template<class T>
	void StaticMatrix4<T>::getInverse(StaticMatrix4& out_inverse) const
	{
	}

	template<class T>
	StaticMatrix4<T> StaticMatrix4<T>::operator *(const StaticMatrix4<T>& mm)
	{
		T newM[16];
		
		newM[0] = (this->getRow(0)*mm.getColumn(0));
		newM[1] = (this->getRow(1)*mm.getColumn(0));
		newM[2] = (this->getRow(2)*mm.getColumn(0));
		newM[3] = (this->getRow(3)*mm.getColumn(0));

		newM[4] = (this->getRow(0)*mm.getColumn(1));
		newM[5] = (this->getRow(1)*mm.getColumn(1));
		newM[6] = (this->getRow(2)*mm.getColumn(1));
		newM[7] = (this->getRow(3)*mm.getColumn(1));

		newM[8] = (this->getRow(0)*mm.getColumn(2));
		newM[9] = (this->getRow(1)*mm.getColumn(2));
		newM[10] = (this->getRow(2)*mm.getColumn(2));
		newM[11] = (this->getRow(3)*mm.getColumn(2));

		newM[12] = (this->getRow(0)*mm.getColumn(3));
		newM[13] = (this->getRow(1)*mm.getColumn(3));
		newM[14] = (this->getRow(2)*mm.getColumn(3));
		newM[15] = (this->getRow(3)*mm.getColumn(3));

		/*newM[0] = (this->getColumn(0)*mm.getRow(0));
		newM[1] = (this->getColumn(1)*mm.getRow(0));
		newM[2] = (this->getColumn(2)*mm.getRow(0));
		newM[3] = (this->getColumn(3)*mm.getRow(0));

		newM[4] = (this->getColumn(0)*mm.getRow(1));
		newM[5] = (this->getColumn(1)*mm.getRow(1));
		newM[6] = (this->getColumn(2)*mm.getRow(1));
		newM[7] = (this->getColumn(3)*mm.getRow(1));

		newM[8] = (this->getColumn(0)*mm.getRow(2));
		newM[9] = (this->getColumn(1)*mm.getRow(2));
		newM[10] = (this->getColumn(2)*mm.getRow(2));
		newM[11] = (this->getColumn(3)*mm.getRow(2));

		newM[12] = (this->getColumn(0)*mm.getRow(3));
		newM[13] = (this->getColumn(1)*mm.getRow(3));
		newM[14] = (this->getColumn(2)*mm.getRow(3));
		newM[15] = (this->getColumn(3)*mm.getRow(3));*/
		
		return StaticMatrix4<T>(newM);
	}

	template<class T>
	Math3d::Vector4D<T> operator *(const StaticMatrix4<T>& m, const Math3d::Vector4D<T>& v)
	{
		Math3d::Vector4D<T> result;
		result.x = v*m.getRow(0);
		result.y = v*m.getRow(1);
		result.z = v*m.getRow(2);
		result.w = v*m.getRow(3);
		return result;
	}
	template<class T>
	Math3d::Vector4D<T> operator*(const Math3d::Vector4D<T>& v, const StaticMatrix4<T>& m)
	{
		Math3d::Vector4D<T> result;
		result.x = v*m.getColumn(0);
		result.y = v*m.getColumn(1);
		result.z = v*m.getColumn(2);
		result.w = v*m.getColumn(3);

		return result;
	}

	template<class T>
	void StaticMatrix4<T>::look_at(const Math3d::Vector3D<T>& position, const Math3d::Vector3D<T>& target, const Math3d::Vector3D<T>& up, StaticMatrix4<T>& out_lookat)
	{
		Math3d::Vector3D<T> zaxis = -(target - position).normalize();
		Math3d::Vector3D<T> xaxis = ((up^zaxis)).normalize();
		Math3d::Vector3D<T> yaxis = (zaxis^xaxis).normalize();


		out_lookat.setRow( 0, Math3d::Vector4D<T>(-xaxis.x, -yaxis.x, -zaxis.x, 0) );
		out_lookat.setRow( 1, Math3d::Vector4D<T>(xaxis.y, yaxis.y, zaxis.y, 0) );
		out_lookat.setRow( 2, Math3d::Vector4D<T>(-xaxis.z, -yaxis.z, -zaxis.z, 0) );
		out_lookat.setRow( 3, Math3d::Vector4D<T>(0, 0, 0, 1) );
		//out_lookat.setRow( 3, Math3d::Vector4D<T>(-(xaxis*position), -(yaxis*position), -(zaxis*position), 1) );
	}
	template<class T>
	Math3d::Vector3D<T> StaticMatrix4<T>::get_rotation() const
	{
		const T toDegrees = static_cast<T>(180.0/3.141593);
		return Math3d::Vector3D<T>( atan2( get(1,2), get(2,2) )*toDegrees,
									asin( -get(0,2) )*toDegrees,
									atan2( get(0,1), get(0,0) )*toDegrees
			);
	}
	

};