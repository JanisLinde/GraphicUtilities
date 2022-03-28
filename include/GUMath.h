#ifndef _GUMATH_H_
#define _GUMATH_H_

#include <math.h>

namespace GU
{
	#define PI 3.1415926

	/*********************************************************/
	inline float det2x2(float m11, float m12, float m21, float m22)
	{
		return m11 * m22 - m12 * m21;
	}

	inline float det3x3(float m11, float m12, float m13,
		float m21, float m22, float m23,
		float m31, float m32, float m33)
	{
		float det = 0.0f;
		det += m11 * det2x2(m22, m32, m23, m33);
		det -= m12 * det2x2(m21, m31, m23, m33);
		det += m13 * det2x2(m21, m31, m22, m32);
		return det;
	}

	inline float max(float a, float b)
	{
		if(a >= b)
			return a;
		else	
			return b;
	}

	inline float min(float a, float b)
	{
		if(a < b)
			return a;
		else
			return b;
	}

	inline float sat(float a)
	{
		return min(1.0f, max(0.0f, a));
	}

	/*********************************************************/
	class Vector2;
	class Vector3;
	class Vector4;
	/*********************************************************/
	typedef Vector4 Vector;
	/*********************************************************/
	class Vector2
	{
		public:
			Vector2() : _x(0), _y(0) { }
			Vector2(const Vector2 &v) : _x(v._x), _y(v._y) { }
			Vector2(float x, float y) : _x(x), _y(y) { }

			float dot(const Vector2 &v);
			float length();
			float length2();

			Vector2 reflect(const Vector2 &n);
			Vector2 normalize();
			Vector2 saturate();

		public:
			float _x, _y;
	};

	inline Vector2 operator + (const Vector2 &a, const Vector2 &b)
	{ return Vector2(a._x + b._x, a._y + a._y); }
	inline void operator += (Vector2 &a, const Vector2 &b)
	{ a._x += b._x; a._y += b._y; }
	inline Vector2 operator - (const Vector2 a)
	{ return Vector2(-a._x, -a._y); }
	inline Vector2 operator - (const Vector2 &a, const Vector2 &b)
	{ return Vector2(a._x - b._x, a._y - a._y); }
	inline void operator -= (Vector2 &a, const Vector2 &b)
	{ a._x -= b._x; a._y -= b._y; }
	inline Vector2 operator * (const Vector2 &a, const float &b)
	{ return Vector2(a._x * b, a._y * b); }
	inline Vector2 operator * (const float &a, const Vector2 &b)
	{ return Vector2(b._x * a, b._y * a); }
	inline Vector2 operator / (const Vector2 &a, const float b)
	{ return Vector2(a._x / b, a._y / b); }
	inline bool operator == (const Vector2 &a, const Vector2 &b)
	{ 
		if(a._x == b._x && a._y == b._y)
			return true;
		else
			return false;
	}
	inline bool operator != (const Vector2 &a, const Vector2 &b)
	{
		if(a._x != b._x || a._y != b._y)
			return true;
		else
			return false;
	}

	inline float Vector2::dot(const Vector2 &v)
	{
		return _x * v._x + _y * v._y;
	}

	inline float Vector2::length()
	{ 
		return (float)sqrt(_x * _x + _y * _y); 
	}

	inline float Vector2::length2()
	{ 
		return _x * _x + _y * _y; 
	}

	inline Vector2 Vector2::reflect(const Vector2 &n)
	{
		float d = this->dot(n);
		float x = _x - 2.0f * d * n._x;
		float y = _y - 2.0f * d * n._y;
		return Vector2(x, y);
	}

	inline Vector2 Vector2::normalize()
	{
		float l = this->length();
		return Vector2(_x /= l, _y /= l);
	}
			
	inline Vector2 Vector2::saturate()
	{
		float x = sat(_x);
		float y = sat(_y);
		return Vector2(x, y);
	}

	/*********************************************************/
	class Vector3
	{
		public:
			Vector3() : _x(0), _y(0), _z(0) {}
			Vector3(const Vector3 &v) : _x(v._x), _y(v._y), _z(v._z) {}
			Vector3(float x, float y, float z) : _x(x), _y(y), _z(z) {}

			float dot(const Vector3 &v);
			float length();
			float length2();

			Vector3 reflect(const Vector3 &n);
			Vector3 normalize();
			Vector3 cross(const Vector3 &a);
			Vector3 saturate();

		public:
			float _x, _y, _z;

	};

	inline Vector3 operator + (const Vector3 &a, const Vector3 &b)
	{ return Vector3(a._x + b._x, a._y + b._y, a._z + b._z); }
	inline void operator += (Vector3 &a, const Vector3 &b)
	{ a._x += b._x; a._y += b._y; a._z += b._z; }
	inline Vector3 operator -(const Vector3 a)
	{ return Vector3(-a._x, -a._y, -a._z); }
	inline Vector3 operator - (const Vector3 &a, const Vector3 &b)
	{ return Vector3(a._x - b._x, a._y - b._y, a._z - b._z); }
	inline void operator -= (Vector3 &a, const Vector3 &b)
	{ a._x -= b._x; a._y -= b._y; a._z -= b._z; }
	inline Vector3 operator * (const Vector3 &a, const Vector3 &b)
	{ return Vector3(a._x * b._x, a._y * b._y, a._z * b._z); }
	inline Vector3 operator * (const Vector3 &a, const float &b)
	{ return Vector3(a._x * b, a._y * b, a._z * b); }
	inline Vector3 operator * (const float &a, const Vector3 &b)
	{ return Vector3(b._x * a, b._y * a, b._z * a); }
	inline Vector3 operator / (const Vector3 &a, const float b)
	{ return Vector3(a._x / b, a._y / b, a._z / b); }
	inline bool operator == (const Vector3 &a, const Vector3 &b)
	{
		if(a._x == b._x && a._y == b._y && a._z == b._z)
			return true;
		else
			return false;
	}
	inline bool operator != (const Vector3 &a, const Vector3 &b)
	{
		if(a._x != b._x || a._y != b._y || a._z != b._z)
			return true;
		else
			return false;
	}

	inline float Vector3::dot(const Vector3 &v)
	{
		return _x * v._x + _y * v._y + _z * v._z;
	}

	inline float Vector3::length()
	{
		return (float)sqrt(_x * _x + _y * _y + _z * _z);
	}

	inline float Vector3::length2()
	{
		return _x * _x + _y * _y + _z * _z;
	}

	inline Vector3 Vector3::reflect(const Vector3 &n)
	{
		float d = this->dot(n);
		float x = _x - 2.0f * d * n._x;
		float y = _y - 2.0f * d * n._y;
		float z = _z - 2.0f * d * n._z;
		return Vector3(x, y, z);
	}

	inline Vector3 Vector3::normalize()
	{
		float l = this->length();
		return Vector3(_x / l, _y / l, _z / l);
	}

	inline Vector3 Vector3::cross(const Vector3 &a)
	{
		return Vector3(_y * a._z - _z * a._y, _z * a._x - _x * a._z, _x * a._y - _y * a._x);
	}

	inline Vector3 Vector3::saturate()
	{
		float x = sat(_x);
		float y = sat(_y);
		float z = sat(_z);
		return Vector3(x, y, z);
	}

	/*********************************************************/
	class Vector4
	{
		public:
			Vector4() : _x(0), _y(0), _z(0), _w(0) { }
			Vector4(const Vector4 &v) 
				: _x(v._x), _y(v._y), _z(v._z), _w(v._w) { }
			Vector4(float x, float y, float z, float w) 
				: _x(x), _y(y), _z(z), _w(w) { }
			Vector4(Vector3 v, float w)
				: _x(v._x), _y(v._y), _z(v._z), _w(w) { }
			Vector4(Vector3 v)
				: _x(v._x), _y(v._y), _z(v._z), _w(1.0f) { }

			float dot(const Vector4 &v);
			float length();
			float length2();

			Vector4 reflect(const Vector4 &n);
			Vector4 normalize();
			Vector4 cross(const Vector4 &a);
			Vector4 saturate();

		public:
			float _x, _y, _z, _w;

	}; 

	inline Vector4 operator + (const Vector4 &a, const Vector4 &b)
	{ return Vector4(a._x + b._x, a._y + a._y, a._z + b._z, a._w + b._w); }
	inline void operator += (Vector4 &a, const Vector4 &b)
	{ a._x += b._x; a._y += b._y; a._z += b._z; a._w += b._w; }
	inline Vector4 operator -(const Vector4 a)
	{ return Vector4(-a._x, -a._y, -a._z, -a._w); }
	inline Vector4 operator - (const Vector4 &a, const Vector4 &b)
	{ return Vector4(a._x - b._x, a._y - a._y, a._z - b._z, a._w - b._w); }
	inline void operator -= (Vector4 &a, const Vector4 &b)
	{ a._x -= b._x; a._y -= b._y; a._z -= b._z; a._w -= b._w; }
	inline Vector4 operator * (const Vector4 &a, const float &b)
	{ return Vector4(a._x * b, a._y * b, a._z * b, a._w * b); }
	inline Vector4 operator * (const float &a, const Vector4 &b)
	{ return Vector4(b._x * a, b._y * a, b._z * a, b._w * a); }
	inline Vector4 operator / (const Vector4 &a, const float b)
	{ return Vector4(a._x / b, a._y / b, a._z / b, a._w / b); }
	inline bool operator == (const Vector4 &a, const Vector4 &b)
	{
		if(a._x == b._x && a._y == b._y && a._z == b._z && a._w == b._w)
			return true;
		else
			return false;
	}
	inline bool operator != (const Vector4 &a, const Vector4 &b)
	{
		if(a._x != b._x || a._y != b._y || a._z != b._z || a._w != b._w)
			return true;
		else
			return false;
	}

	inline float Vector4::dot(const Vector4 &v)
	{
		return _x * v._x + _y * v._y + _z * v._z;
	}

	inline float Vector4::length()
	{
		return (float)sqrt(_x * _x + _y * _y + _z * _z);
	}

	inline float Vector4::length2()
	{
		return _x * _x + _y * _y + _z * _z;
	}

	inline Vector4 Vector4::reflect(const Vector4 &n)
	{
		float d = this->dot(n);
		float x = _x - 2.0f * d * n._x;
		float y = _y - 2.0f * d * n._y;
		float z = _z - 2.0f * d * n._z;
		return Vector4(x, y, z, 1);
	}

	inline Vector4 Vector4::normalize()
	{
		float l = this->length();
		return Vector4(_x / l, _y / l, _z / l, 1.0);
	}

	inline Vector4 Vector4::cross(const Vector4 &a)
	{
		return Vector4(_y * a._z - _z * a._y, _z * a._x - _x * a._z, _x * a._y - _y * a._x, 1.0);
	}

	inline Vector4 Vector4::saturate()
	{
		float x = sat(_x);
		float y = sat(_y);
		float z = sat(_z);
		float w = sat(_w);
		return Vector4(x, y, z, w);		
	}

	/*********************************************************/



	/*********************************************************/
	class Matrix2x2;
	class Matrix3x3;
	class Matrix4x4;
	/*********************************************************/
	typedef Matrix4x4 Matrix;
	/*********************************************************/
	class Matrix2x2
	{
		public:
			Matrix2x2() : _m11(1), _m12(0), _m21(0), _m22(1) { }
			Matrix2x2(Matrix2x2 &m)
				: _m11(m._m11), _m12(m._m12), 
				_m21(m._m21), _m22(m._m22) { }
			Matrix2x2(float m11, float m12, float m21, float m22)
				: _m11(m11), _m12(m12), _m21(m21), _m22(m22) { }

			Matrix2x2 inverse();
			Matrix2x2 transpose();

		public:
			float _m11, _m12;
			float _m21, _m22;

	};

	inline Matrix2x2 operator + (const Matrix2x2 &a, const Matrix2x2 &b)
	{
		return Matrix2x2(
			a._m11 + b._m11, a._m12 + b._m12,
			a._m21 + b._m21, a._m22 + b._m22
		);
	}
	inline Matrix2x2 operator - (const Matrix2x2 &a, const Matrix2x2 &b)
	{
		return Matrix2x2(
			a._m11 - b._m11, a._m12 - b._m12,
			a._m21 - b._m21, a._m22 - b._m22
		);
	}
	inline Matrix2x2 operator * (const Matrix2x2 &a, const float s)
	{
		return Matrix2x2(
			a._m11 * s, a._m12 * s,
			a._m21 * s, a._m22 * s
		);
	}
	inline Matrix2x2 operator * (const float s, const Matrix2x2 &a)
	{
		return Matrix2x2(
			a._m11 * s, a._m12 * s,
			a._m21 * s, a._m22 * s
		);
	}
	inline Matrix2x2 operator * (const Matrix2x2 &a, const Matrix2x2 &b)
	{
		Matrix2x2 r;

		r._m11 = a._m11 * b._m11 + a._m12 * b._m21;
		r._m12 = a._m11 * b._m21 + a._m12 * b._m22;
		r._m21 = a._m21 * b._m11 + a._m22 * b._m21;
		r._m22 = a._m21 * b._m21 + a._m22 * b._m22;

		return r;
	}
	inline Vector2 operator * (const Matrix2x2 &a, const Vector2 &b)
	{
		Vector2 r;

		r._x = a._m11 * b._x + a._m12 * b._y;
		r._y = a._m21 * b._x + a._m22 * b._y;

		return r;
	}
	inline Matrix2x2 operator / (const Matrix2x2 &a, const float s)
	{
		return Matrix2x2(
			a._m11 / s, a._m12 / s,
			a._m21 / s, a._m22 / s
		);
	}

	inline Matrix2x2 Matrix2x2::inverse()
	{
		float det = _m11 * _m22 - _m12 * _m21;
		Matrix2x2 i;

		i._m11 = _m22 / det;
		i._m12 = -_m12 / det;
		i._m21 = -_m21 / det;
		i._m22 = _m11 / det;

		return i;
	}

	inline Matrix2x2 Matrix2x2::transpose()
	{
		Matrix2x2 t;
		t._m11 = _m11;
		t._m12 = _m21;
		t._m21 = _m12;
		t._m22 = _m22;

		return t;
	}

	/*********************************************************/
	class Matrix3x3
	{
		public:
			Matrix3x3()
				: _m11(1), _m12(0), _m13(0),
				_m21(0), _m22(1), _m23(0),
				_m31(0), _m32(0), _m33(1) { }
			Matrix3x3(Matrix3x3 &m)
				: _m11(m._m11), _m12(m._m12), _m13(m._m13),
				_m21(m._m21), _m22(m._m22), _m23(m._m23),
				_m31(m._m31), _m32(m._m32), _m33(m._m33) { }
			Matrix3x3(float m11, float m12, float m13,
				float m21, float m22, float m23,
				float m31, float m32, float m33)
				: _m11(m11), _m12(m12), _m13(m13),
				_m21(m21), _m22(m22), _m23(m23),
				_m31(m31), _m32(m32), _m33(m33) { }

			Matrix3x3 inverse();
			Matrix3x3 transpose();

		public:
			float _m11, _m12, _m13;
			float _m21, _m22, _m23;
			float _m31, _m32, _m33;

	};

	inline Matrix3x3 operator + (const Matrix3x3 &a, const Matrix3x3 &b)
	{
		return Matrix3x3(
			a._m11 + b._m11, a._m12 + b._m12, a._m13 + b._m13,
			a._m21 + b._m21, a._m22 + b._m22, a._m23 + b._m23,
			a._m31 + b._m31, a._m32 + b._m32, a._m33 + b._m33
		);
	}
	inline Matrix3x3 operator - (const Matrix3x3 &a, const Matrix3x3 &b)
	{
		return Matrix3x3(
			a._m11 - b._m11, a._m12 - b._m12, a._m13 - b._m13,
			a._m21 - b._m21, a._m22 - b._m22, a._m23 - b._m23,
			a._m31 - b._m31, a._m32 - b._m32, a._m33 - b._m33
		);
	}
	inline Matrix3x3 operator * (const Matrix3x3 &a, const float s)
	{
		return Matrix3x3(
			a._m11 * s, a._m12 * s, a._m13 * s,
			a._m21 * s, a._m22 * s, a._m23 * s,
			a._m31 * s, a._m32 * s, a._m33 * s

		);
	}
	inline Matrix3x3 operator * (const float s, const Matrix3x3 &a)
	{
		return Matrix3x3(
			a._m11 * s, a._m12 * s, a._m13 * s,
			a._m21 * s, a._m22 * s, a._m23 * s,
			a._m31 * s, a._m32 * s, a._m33 * s

		);
	}
	inline Matrix3x3 operator * (const Matrix3x3 &a, const Matrix3x3 &b)
	{
		Matrix3x3 r;
		r._m11 = a._m11 * b._m11 + a._m12 * b._m21 + a._m13 * b._m31;
		r._m12 = a._m11 * b._m12 + a._m12 + b._m22 + a._m13 + b._m32;
		r._m13 = a._m11 * b._m13 + a._m12 * b._m23 + a._m13 * b._m33;

		r._m21 = a._m21 * b._m11 + a._m22 * b._m21 + a._m23 * b._m31;
		r._m22 = a._m21 * b._m12 + a._m22 * b._m22 + a._m23 * b._m32;
		r._m23 = a._m21 * b._m13 + a._m22 * b._m23 + a._m23 * b._m33;

		r._m31 = a._m31 * b._m11 + a._m32 * b._m21 + a._m33 * b._m31;
		r._m32 = a._m31 * b._m12 + a._m32 * b._m22 + a._m33 * b._m32;
		r._m33 = a._m31 * b._m13 + a._m32 * b._m23 + a._m33 * b._m33;
		return r;
	}
	inline Vector3 operator * (const Matrix3x3 &a, const Vector3 &b)
	{
		return Vector3(
			a._m11 * b._x + a._m12 * b._y + a._m13 * b._z,
			a._m21 * b._x + a._m22 * b._y + a._m23 * b._z,
			a._m31 * b._x + a._m32 * b._y + a._m33 * b._z		
		);
	}
	inline Matrix3x3 operator / (const Matrix3x3 &a, const float s)
	{
		return Matrix3x3(
			a._m11 / s, a._m12 / s, a._m13 / s,
			a._m21 / s, a._m22 / s, a._m23 / s,
			a._m31 / s, a._m32 / s, a._m33 / s
		);
	}

	inline Matrix3x3 Matrix3x3::inverse()
	{
		Matrix3x3 i;

		float det = 0.0f;
		det += _m11 * det2x2(_m22, _m32, _m32, _m33);
		det -= _m12 * det2x2(_m21, _m31, _m23, _m33);
		det += _m13 * det2x2(_m21, _m31, _m22, _m32);

		i._m11 = det2x2(_m22, _m32, _m23, _m33) / det;
		i._m21 = -det2x2(_m21, _m31, _m23, _m33) / det;
		i._m31 = det2x2(_m21, _m31, _m22, _m32) / det;

		i._m12 = -det2x2(_m12, _m32, _m13, _m33) / det;
		i._m22 = det2x2(_m11, _m31, _m13, _m33) / det;
		i._m32 = -det2x2(_m11, _m31, _m12, _m32) / det;

		i._m13 = det2x2(_m12, _m22, _m13, _m23) / det;
		i._m23 = -det2x2(_m11, _m21, _m13, _m23) / det;
		i._m33 = det2x2(_m11, _m21, _m12, _m22) / det;

		return i;
	}

	inline Matrix3x3 Matrix3x3::transpose()
	{
		Matrix3x3 t;
		t._m11 = _m11; t._m12 = _m21; t._m13 = _m31;
		t._m21 = _m12; t._m22 = _m22; t._m23 = _m32;
		t._m31 = _m13; t._m32 = _m23; t._m33 = _m33;
		return t;
	}

	/*********************************************************/
	class Matrix4x4
	{
		public:
			Matrix4x4()
				: _m11(1), _m12(0), _m13(0), _m14(0),
				_m21(0), _m22(1), _m23(0), _m24(0),
				_m31(0), _m32(0), _m33(1), _m34(0),
				_m41(0), _m42(0), _m43(0), _m44(1) { }
			Matrix4x4(Matrix4x4 &m)
				: _m11(m._m11), _m12(m._m12), _m13(m._m13), _m14(m._m14), 
				_m21(m._m21), _m22(m._m22), _m23(m._m23), _m24(m._m24),
				_m31(m._m31), _m32(m._m32), _m33(m._m33), _m34(m._m34),
				_m41(m._m41), _m42(m._m42), _m43(m._m43), _m44(m._m44) { }
			Matrix4x4(float m11, float m12, float m13, float m14,
				float m21, float m22, float m23, float m24,
				float m31, float m32, float m33, float m34,
				float m41, float m42, float m43, float m44)
				: _m11(m11), _m12(m12), _m13(m13), _m14(m14),
				_m21(m21), _m22(m22), _m23(m23), _m24(m24),
				_m31(m31), _m32(m32), _m33(m33), _m34(m34),
				_m41(m41), _m42(m42), _m43(m43), _m44(m44) { }

			Matrix4x4 inverse();
			Matrix4x4 transpose();

		public:
			float _m11, _m12, _m13, _m14;
			float _m21, _m22, _m23, _m24;
			float _m31, _m32, _m33, _m34;
			float _m41, _m42, _m43, _m44;

	};

	inline Matrix4x4 operator + (const Matrix4x4 &a, const Matrix4x4 &b)
	{
		return Matrix4x4(
			a._m11 + b._m11, a._m12 + b._m12, a._m13 + b._m13, a._m14 + b._m14,
			a._m21 + b._m21, a._m22 + b._m22, a._m23 + b._m23, a._m24 + b._m24,
			a._m31 + b._m31, a._m32 + b._m32, a._m33 + b._m33, a._m34 + b._m34,
			a._m41 + b._m41, a._m42 + b._m42, a._m43 + b._m43, a._m44 + b._m44
		);
	}
	inline Matrix4x4 operator - (const Matrix4x4 &a, const Matrix4x4 &b)
	{
		return Matrix4x4(
			a._m11 - b._m11, a._m12 - b._m12, a._m13 - b._m13, a._m14 - b._m14,
			a._m21 - b._m21, a._m22 - b._m22, a._m23 - b._m23, a._m24 - b._m24,
			a._m31 - b._m31, a._m32 - b._m32, a._m33 - b._m33, a._m34 - b._m34,
			a._m41 - b._m41, a._m42 - b._m42, a._m43 - b._m43, a._m44 - b._m44
		);
	}
	inline Matrix4x4 operator * (const Matrix4x4 &a, const float s)
	{
		return Matrix4x4(
			a._m11 * s, a._m12 * s, a._m13 * s, a._m14 * s,
			a._m21 * s, a._m22 * s, a._m23 * s, a._m24 * s,
			a._m31 * s, a._m32 * s, a._m33 * s, a._m34 * s,
			a._m41 * s, a._m42 * s, a._m43 * s, a._m44 * s
		);
	}
	inline Matrix4x4 operator * (const float s, const Matrix4x4 &a)
	{
		return Matrix4x4(
			a._m11 * s, a._m12 * s, a._m13 * s, a._m14 * s,
			a._m21 * s, a._m22 * s, a._m23 * s, a._m24 * s,
			a._m31 * s, a._m32 * s, a._m33 * s, a._m34 * s,
			a._m41 * s, a._m42 * s, a._m43 * s, a._m44 * s
		);
	}
	inline Matrix4x4 operator * (const Matrix4x4 &a, const Matrix4x4 &b)
	{
		Matrix4x4 r;
		r._m11 = a._m11 * b._m11 + a._m12 * b._m21 + a._m13 * b._m31 + a._m14 * b._m41;
		r._m12 = a._m11 * b._m12 + a._m12 * b._m22 + a._m13 * b._m32 + a._m14 * b._m42;
		r._m13 = a._m11 * b._m13 + a._m12 * b._m23 + a._m13 * b._m33 + a._m14 * b._m43;
		r._m14 = a._m11 * b._m14 + a._m12 * b._m24 + a._m13 * b._m34 + a._m14 * b._m44;

		r._m21 = a._m21 * b._m11 + a._m22 * b._m21 + a._m23 * b._m31 + a._m24 * b._m41;
		r._m21 = a._m21 * b._m12 + a._m22 * b._m22 + a._m23 * b._m32 + a._m24 * b._m42;
		r._m21 = a._m21 * b._m13 + a._m22 * b._m23 + a._m23 * b._m33 + a._m24 * b._m43;
		r._m21 = a._m21 * b._m14 + a._m22 * b._m24 + a._m23 * b._m34 + a._m24 * b._m44;

		r._m31 = a._m31 * b._m11 + a._m32 * b._m21 + a._m33 * b._m31 + a._m34 * b._m41;
		r._m31 = a._m31 * b._m12 + a._m32 * b._m22 + a._m33 * b._m32 + a._m34 * b._m42;
		r._m31 = a._m31 * b._m13 + a._m32 * b._m23 + a._m33 * b._m33 + a._m34 * b._m43;
		r._m31 = a._m31 * b._m14 + a._m32 * b._m24 + a._m33 * b._m34 + a._m34 * b._m44;

		r._m41 = a._m41 * b._m11 + a._m42 * b._m21 + a._m43 * b._m31 + a._m24 * b._m41;
		r._m41 = a._m41 * b._m12 + a._m42 * b._m22 + a._m43 * b._m32 + a._m44 * b._m42;
		r._m41 = a._m41 * b._m13 + a._m42 * b._m23 + a._m43 * b._m33 + a._m44 * b._m43;
		r._m41 = a._m41 * b._m14 + a._m42 * b._m24 + a._m43 * b._m34 + a._m44 * b._m44;
		return r;
	}
	inline Vector4 operator * (const Matrix4x4 &a, const Vector4 &b)
	{
		return Vector4(
			a._m11 * b._x + a._m12 * b._y + a._m13 * b._z + a._m14 * b._w,
			a._m21 * b._x + a._m22 * b._y + a._m23 * b._z + a._m24 * b._w,
			a._m31 * b._x + a._m32 * b._y + a._m33 * b._z + a._m34 * b._w,
			a._m41 * b._x + a._m42 * b._y + a._m43 * b._z + a._m44 * b._w
		);
	}
	inline Matrix4x4 operator / (const Matrix4x4 &a, const float s)
	{
		return Matrix4x4(
			a._m11 / s, a._m12 / s, a._m13 / s, a._m14 / s,
			a._m21 / s, a._m22 / s, a._m23 / s, a._m24 / s,
			a._m31 / s, a._m32 / s, a._m33 / s, a._m34 / s,
			a._m41 / s, a._m42 / s, a._m43 / s, a._m44 / s
		);
	}

	inline Matrix4x4 Matrix4x4::inverse()
	{
		float det = 0.0f;
		det += _m11 * det3x3(_m22, _m32, _m42, _m23, _m33, _m43, _m24, _m34, _m44);
		det -= _m12 * det3x3(_m21, _m31, _m41, _m23, _m33, _m43, _m24, _m34, _m44);
		det += _m13 * det3x3(_m21, _m31, _m41, _m22, _m32, _m42, _m24, _m34, _m44);
		det -= _m14 * det3x3(_m21, _m31, _m41, _m22, _m32, _m42, _m23, _m33, _m43);

		Matrix4x4 i;
		i._m11 = det3x3(_m22, _m32, _m42, _m23, _m33, _m43, _m24, _m34, _m44) / det;
		i._m21 = -det3x3(_m21, _m31, _m41, _m23, _m33, _m43, _m24, _m34, _m44) / det;
		i._m31 = det3x3(_m21, _m31, _m41, _m22, _m32, _m42, _m24, _m34, _m44) / det;
		i._m41 = -det3x3(_m21, _m31, _m41, _m22, _m32, _m42, _m23, _m33, _m43) / det;

		i._m12 = -det3x3(_m12, _m32, _m42, _m13, _m33, _m43, _m41, _m34, _m44) / det;
		i._m22 = det3x3(_m11, _m31, _m41, _m13, _m33, _m43, _m14, _m34, _m44) / det;
		i._m32 = -det3x3(_m11, _m31, _m41, _m12, _m32, _m42, _m14, _m34, _m44) / det;
		i._m42 = det3x3(_m11, _m31, _m41, _m12, _m32, _m42, _m13, _m33, _m43) / det;

		i._m13 = det3x3(_m12, _m22, _m42, _m13, _m23, _m43, _m14, _m24, _m44) / det;
		i._m23 = -det3x3(_m11, _m21, _m41, _m13, _m23, _m43, _m14, _m24, _m44) / det;
		i._m33 = det3x3(_m11, _m21, _m41, _m12, _m22, _m42, _m14, _m24, _m44) / det;
		i._m43 = -det3x3(_m11, _m21, _m41, _m12, _m22, _m42, _m13, _m23, _m43) / det;

		i._m14 = -det3x3(_m12, _m22, _m32, _m13, _m23, _m33, _m14, _m24, _m34) / det;
		i._m24 = det3x3(_m11, _m21, _m31, _m13, _m23, _m33, _m14, _m24, _m34) / det;
		i._m34 = -det3x3(_m11, _m21, _m31, _m12, _m22, _m32, _m14, _m24, _m34) / det;
		i._m44 = det3x3(_m11, _m21, _m31, _m12, _m22, _m32, _m13, _m23, _m33) / det;

		return i;
	}

	inline Matrix4x4 Matrix4x4::transpose()
	{
		return Matrix4x4(
			_m11, _m21, _m31, _m41, 
			_m12, _m22, _m32, _m42,
			_m13, _m23, _m33, _m34,
			_m14, _m24, _m34, _m44
		);
	}
	/*********************************************************/

	inline Matrix MatrixTranslate(float x, float y, float z)
	{
		Matrix t;
		t._m14 = x;
		t._m24 = y;
		t._m34 = z;
		return t;
	}

	inline Matrix MatrixScale(float x, float y, float z)
	{
		Matrix s;
		s._m11 = x;
		s._m22 = y;
		s._m33 = z;
		return s;
	}

	inline Matrix MatrixRotateX(float x)
	{
		Matrix r;
		r._m22 = (float)cos(x);	r._m23 = (float)-sin(x);
		r._m32 = (float)sin(x);	r._m33 = (float)cos(x);
		return r;
	}

	inline Matrix MatrixRotateY(float y)
	{
		Matrix r;
		r._m11 = (float)cos(y);	r._m13 = (float)-sin(y);
		r._m31 = (float)sin(y);	r._m33 = (float)cos(y);
		return r;
	}

	inline Matrix MatrixRotateZ(float z)
	{
		Matrix r;
		r._m11 = (float)cos(z);	r._m12 = (float)-sin(z);
		r._m21 = (float)sin(z);	r._m22 = (float)cos(z);
		return r;
	}

	inline Matrix MatrixRotateXYZ(float x, float y, float z)
	{
		return MatrixRotateX(x) * MatrixRotateY(y) * MatrixRotateZ(z);
	}

	inline Matrix MatrixLookAt(Vector &eye, Vector &lookAt, Vector &up)
	{
		Vector Z = (eye - lookAt).normalize();
		Vector X = up.cross(Z);
		Vector Y = Z.cross(X);

		Matrix view;

		view._m11 = X._x;
		view._m21 = X._y;
		view._m31 = X._z;
		view._m12 = Y._x;
		view._m22 = Y._y;
		view._m32 = Y._z;
		view._m13 = Z._x;
		view._m23 = Z._y;
		view._m33 = Z._z;
		view._m14 = eye._x;
		view._m24 = eye._y;
		view._m34 = eye._z;
		return view;
	}

}

#endif