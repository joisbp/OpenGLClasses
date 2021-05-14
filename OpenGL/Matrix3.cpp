#include "Matrix3.h"

template<> const Matrix3<float> Matrix3<float>::IDENTITY(1, 0, 0, 0, 1, 0, 0, 0, 1);
template<> const Matrix3<float> Matrix3<float>::ZERO(0, 0, 0, 0, 0, 0, 0, 0, 0);