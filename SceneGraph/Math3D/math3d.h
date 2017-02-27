// Math3d.h

#pragma once

#include "matrix.h"
#include "staticmatrix4.h"
#include "vector4.h"

#define PI 3.1415967 
typedef double Real;

typedef Math3d::Vector3D<double> Dvector;
typedef Math3d::Vector3D<float> Fvector;
typedef Math3d::Vector3D<Real> Rvector;

typedef Math3d::Vector2D<double> Dvector2;
typedef Math3d::Vector2D<float> Fvector2;
typedef Math3d::Vector2D<Real> Rvector2;

typedef Math3d::Vector4D<double> Dvector4;
typedef Math3d::Vector4D<float> Fvector4;
typedef Math3d::Vector4D<Real> Rvector4;

typedef Math3d::Ray3D<double> Dray;
typedef Math3d::Ray3D<float> Fray;

typedef Math3d::Matrix3D<double> Dmatrix;
typedef Math3d::Matrix3D<float> Fmatrix;
typedef Math3d::StaticMatrix4<float> FSmatrix4;
