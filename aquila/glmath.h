//Disclaimer:: This code does not belong to me nor did I create it in the first place
//However, I did implement several additions to the existing structures. I have marked those with "Shao Kun Deng" comments

// ----------------------------------------------------------------------------------------------------------------------------
//
// Version 2.04
//
// ----------------------------------------------------------------------------------------------------------------------------

#ifndef _glmath_
#define _glmath_

#define _USE_MATH_DEFINES

#include "Utils.h"

#include <math.h>
#include <string>

// ----------------------------------------------------------------------------------------------------------------------------

class vec2
{
public:
	union{
		struct{double x, y;};
		struct{double s, t;};
		struct{double r, g;};
	};
	vec2() : x(0.0), y(0.0){}
	~vec2(){}
	vec2(double num) : x(num), y(num){}
	vec2(double x, double y) : x(x), y(y){}
	vec2(const vec2 &u) : x(u.x), y(u.y){}
	vec2& operator = (const vec2 &u){x = u.x; y = u.y; return *this;}
	vec2 operator - (){return vec2(-x, -y);}
	//double* operator & (){return (double*)this;};
	vec2& operator += (double num){x += num; y += num; return *this;}
	vec2& operator += (const vec2 &u){x += u.x; y += u.y; return *this;}
	vec2& operator -= (double num){x -= num; y -= num; return *this;}
	vec2& operator -= (const vec2 &u){x -= u.x; y -= u.y; return *this;}
	vec2& operator *= (double num){x *= num; y *= num; return *this;}
	vec2& operator *= (const vec2 &u){x *= u.x; y *= u.y; return *this;}
	vec2& operator /= (double num){x /= num; y /= num; return *this;}
	vec2& operator /= (const vec2 &u){x /= u.x; y /= u.y; return *this;}
	friend vec2 operator + (const vec2 &u, double num){return vec2(u.x + num, u.y + num);}
	friend vec2 operator + (double num, const vec2 &u){return vec2(num + u.x, num + u.y);}
	friend vec2 operator + (const vec2 &u, const vec2 &v){return vec2(u.x + v.x, u.y + v.y);}
	friend vec2 operator - (const vec2 &u, double num){return vec2(u.x - num, u.y - num);}
	friend vec2 operator - (double num, const vec2 &u){return vec2(num - u.x, num - u.y);}
	friend vec2 operator - (const vec2 &u, const vec2 &v){return vec2(u.x - v.x, u.y - v.y);}
	friend vec2 operator * (const vec2 &u, double num){return vec2(u.x * num, u.y * num);}
	friend vec2 operator * (double num, const vec2 &u){return vec2(num * u.x, num * u.y);}
	friend vec2 operator * (const vec2 &u, const vec2 &v){return vec2(u.x * v.x, u.y * v.y);}
	friend vec2 operator / (const vec2 &u, double num){return vec2(u.x / num, u.y / num);}
	friend vec2 operator / (double num, const vec2 &u){return vec2(num / u.x, num / u.y);}
	friend vec2 operator / (const vec2 &u, const vec2 &v){return vec2(u.x / v.x, u.y / v.y);}
	
	//Shao Kun Deng
	operator std::string() const { return "("+std::to_string(x)+","+std::to_string(y)+")"; }
	vec2(std::string s) { std::vector<std::string> vs = Utils::explode(s, ' '); x = std::stof(vs[0]); y = std::stof(vs[1]); }
};

// ----------------------------------------------------------------------------------------------------------------------------

double dot(const vec2 &u, const vec2 &v);
double length(const vec2 &u);
double length2(const vec2 &u);
vec2 mix(const vec2 &u, const vec2 &v, double a);
vec2 normalize(const vec2 &u);
vec2 reflect(const vec2 &i, const vec2 &n);
vec2 refract(const vec2 &i, const vec2 &n, double eta);
vec2 rotate(const vec2 &u, double angle);

// ----------------------------------------------------------------------------------------------------------------------------

class vec3
{
public:
	union{
		struct{double x, y, z;};
		struct{double s, t, p;};
		struct{double r, g, b;};
	};
	vec3() : x(0.0), y(0.0), z(0.0){}
	~vec3(){}
	vec3(double num) : x(num), y(num), z(num){}
	vec3(double x, double y, double z) : x(x), y(y), z(z){}
	vec3(const vec2 &u, double z) : x(u.x), y(u.y), z(z){}
	vec3(const vec3 &u) : x(u.x), y(u.y), z(u.z){}
	vec3& operator = (const vec3 &u){x = u.x; y = u.y; z = u.z; return *this;}
	vec3 operator - (){return vec3(-x, -y, -z);}
	//double* operator & (){return (double*)this;}
	vec3& operator += (double num){x += num; y += num; z += num; return *this;}
	vec3& operator += (const vec3 &u){x += u.x; y += u.y; z += u.z; return *this;}
	vec3& operator -= (double num){x -= num; y -= num; z -= num; return *this;}
	vec3& operator -= (const vec3 &u){x -= u.x; y -= u.y; z -= u.z; return *this;}
	vec3& operator *= (double num){x *= num; y *= num; z *= num; return *this;}
	vec3& operator *= (const vec3 &u){x *= u.x; y *= u.y; z *= u.z; return *this;}
	vec3& operator /= (double num){x /= num; y /= num; z /= num; return *this;}
	vec3& operator /= (const vec3 &u){x /= u.x; y /= u.y; z /= u.z; return *this;}
	friend vec3 operator + (const vec3 &u, double num){return vec3(u.x + num, u.y + num, u.z + num);}
	friend vec3 operator + (double num, const vec3 &u){return vec3(num + u.x, num + u.y, num + u.z);}
	friend vec3 operator + (const vec3 &u, const vec3 &v){return vec3(u.x + v.x, u.y + v.y, u.z + v.z);}
	friend vec3 operator - (const vec3 &u, double num){return vec3(u.x - num, u.y - num, u.z - num);}
	friend vec3 operator - (double num, const vec3 &u){return vec3(num - u.x, num - u.y, num - u.z);}
	friend vec3 operator - (const vec3 &u, const vec3 &v){return vec3(u.x - v.x, u.y - v.y, u.z - v.z);}
	friend vec3 operator * (const vec3 &u, double num){return vec3(u.x * num, u.y * num, u.z * num);}
	friend vec3 operator * (double num, const vec3 &u){return vec3(num * u.x, num * u.y, num * u.z);}
	friend vec3 operator * (const vec3 &u, const vec3 &v){return vec3(u.x * v.x, u.y * v.y, u.z * v.z);}
	friend vec3 operator / (const vec3 &u, double num){return vec3(u.x / num, u.y / num, u.z / num);}
	friend vec3 operator / (double num, const vec3 &u){return vec3(num / u.x, num / u.y, num / u.z);}
	friend vec3 operator / (const vec3 &u, const vec3 &v){return vec3(u.x / v.x, u.y / v.y, u.z / v.z);}
	
	//Shao Kun Deng
	operator std::string() const { return "(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z) + ")"; }
	vec3(std::string s) { std::vector<std::string> vs = Utils::explode(s, ' '); x = std::stof(vs[0]); y = std::stof(vs[1]); z = std::stof(vs[2]); }
};

// ----------------------------------------------------------------------------------------------------------------------------

vec3 cross(const vec3 &u, const vec3 &v);
double dot(const vec3 &u, const vec3 &v);
double length(const vec3 &u);
double length2(const vec3 &u);
vec3 mix(const vec3 &u, const vec3 &v, double a);
vec3 normalize(const vec3 &u);
vec3 reflect(const vec3 &i, const vec3 &n);
vec3 refract(const vec3 &i, const vec3 &n, double eta);
vec3 rotate(const vec3 &u, double angle, const vec3 &v);

//Shao Kun Deng
vec3 clamp(const vec3 &u, double min, double max);
vec3 elemul(const vec3& u, const vec3& v);
vec3 mix(const vec3& u, const vec3& v, const vec3& m);
double sum(const vec3& u);

// ----------------------------------------------------------------------------------------------------------------------------

class vec4
{
public:
	union{
		struct{double x, y, z, w;};
		struct{double s, t, p, q;};
		struct{double r, g, b, a;};
	};
	vec4() : x(0.0), y(0.0), z(0.0), w(0.0){}
	~vec4(){}
	vec4(double num) : x(num), y(num), z(num), w(num){}
	vec4(double x, double y, double z, double w) : x(x), y(y), z(z), w(w){}
	vec4(const vec2 &u, double z, double w) : x(u.x), y(u.y), z(z), w(w){}
	vec4(const vec3 &u, double w) : x(u.x), y(u.y), z(u.z), w(w){}
	vec4(const vec4 &u) : x(u.x), y(u.y), z(u.z), w(u.w){}
	vec4& operator = (const vec4 &u){x = u.x; y = u.y; z = u.z; w = u.w; return *this;}
	vec4 operator - (){return vec4(-x, -y, -z, -w);}
	double* operator & (){return (double*)this;}
	vec4& operator += (double num){x += num; y += num; z += num; w += num; return *this;}
	vec4& operator += (const vec4 &u){x += u.x; y += u.y; z += u.z; w += u.w; return *this;}
	vec4& operator -= (double num){x -= num; y -= num; z -= num; w -= num; return *this;}
	vec4& operator -= (const vec4 &u){x -= u.x; y -= u.y; z -= u.z; w -= u.w; return *this;}
	vec4& operator *= (double num){x *= num; y *= num; z *= num; w *= num; return *this;}
	vec4& operator *= (const vec4 &u){x *= u.x; y *= u.y; z *= u.z; w *= u.w; return *this;}
	vec4& operator /= (double num){x /= num; y /= num; z /= num; w /= num; return *this;}
	vec4& operator /= (const vec4 &u){x /= u.x; y /= u.y; z /= u.z; w /= u.w; return *this;}
	friend vec4 operator + (const vec4 &u, double num){return vec4(u.x + num, u.y + num, u.z + num, u.w + num);}
	friend vec4 operator + (double num, const vec4 &u){return vec4(num + u.x, num + u.y, num + u.z, num + u.w);}
	friend vec4 operator + (const vec4 &u, const vec4 &v){return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w);}
	friend vec4 operator - (const vec4 &u, double num){return vec4(u.x - num, u.y - num, u.z - num, u.w - num);}
	friend vec4 operator - (double num, const vec4 &u){return vec4(num - u.x, num - u.y, num - u.z, num - u.w);}
	friend vec4 operator - (const vec4 &u, const vec4 &v){return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w);}
	friend vec4 operator * (const vec4 &u, double num){return vec4(u.x * num, u.y * num, u.z * num, u.w * num);}
	friend vec4 operator * (double num, const vec4 &u){return vec4(num * u.x, num * u.y, num * u.z, num * u.w);}
	friend vec4 operator * (const vec4 &u, const vec4 &v){return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w);}
	friend vec4 operator / (const vec4 &u, double num){return vec4(u.x / num, u.y / num, u.z / num, u.w / num);}
	friend vec4 operator / (double num, const vec4 &u){return vec4(num / u.x, num / u.y, num / u.z, num / u.w);}
	friend vec4 operator / (const vec4 &u, const vec4 &v){return vec4(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w);}
};

// ----------------------------------------------------------------------------------------------------------------------------

class mat2x2;
class mat3x3;
class mat4x4;

// ----------------------------------------------------------------------------------------------------------------------------

class mat2x2
{
public:
	double M[4];
	mat2x2();
	~mat2x2();
	mat2x2(const mat2x2 &Matrix);
	mat2x2(const vec2 &col1, const vec2 &col2);
	mat2x2(double c1r1, double c1r2, double c2r1, double c2r2);
	explicit mat2x2(const mat3x3 &Matrix);
	explicit mat2x2(const mat4x4 &Matrix);
	mat2x2& operator = (const mat2x2 &Matrix);
	double& operator [] (int i);
	double* operator & ();
	friend mat2x2 operator * (const mat2x2 &Matrix1, const mat2x2 &Matrix2);
	friend vec2 operator * (const mat2x2 &Matrix, const vec2 &u);
};

// ----------------------------------------------------------------------------------------------------------------------------

mat2x2 inverse(const mat2x2 &Matrix);
mat2x2 transpose(const mat2x2 &Matrix);

// ----------------------------------------------------------------------------------------------------------------------------

class mat3x3
{
public:
	double M[9];
	mat3x3();
	~mat3x3();
	mat3x3(const mat3x3 &Matrix);
	mat3x3(const vec3 &col1, const vec3 &col2, const vec3 &col3);
	mat3x3(double c1r1, double c1r2, double c1r3, double c2r1, double c2r2, double c2r3, double c3r1, double c3r2, double c3r3);
	explicit mat3x3(const mat2x2 &Matrix);
	explicit mat3x3(const mat4x4 &Matrix);
	mat3x3& operator = (const mat3x3 &Matrix);
	double& operator [] (int i);
	double* operator & ();
	friend mat3x3 operator * (const mat3x3 &Matrix1, const mat3x3 &Matrix2);
	friend vec3 operator * (const mat3x3 &Matrix, const vec3 &u);
};

// ----------------------------------------------------------------------------------------------------------------------------

mat3x3 inverse(const mat3x3 &Matrix);
mat3x3 transpose(const mat3x3 &Matrix);

// ----------------------------------------------------------------------------------------------------------------------------

class mat4x4
{
public:
	double M[16];
	mat4x4();
	~mat4x4();
	mat4x4(const mat4x4 &Matrix);
	mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4);
	mat4x4(double c1r1, double c1r2, double c1r3, double c1r4, double c2r1, double c2r2, double c2r3, double c2r4, double c3r1, double c3r2, double c3r3, double c3r4, double c4r1, double c4r2, double c4r3, double c4r4);
	explicit mat4x4(const mat2x2 &Matrix);
	explicit mat4x4(const mat3x3 &Matrix);
	mat4x4& operator = (const mat4x4 &Matrix);
	double& operator [] (int i);
	double* operator & ();
	friend mat4x4 operator * (const mat4x4 &Matrix1, const mat4x4 &Matrix2);
	friend vec4 operator * (const mat4x4 &Matrix, const vec4 &u);
};

// ----------------------------------------------------------------------------------------------------------------------------

extern mat4x4 BiasMatrix;
extern mat4x4 BiasMatrixInverse;

// ----------------------------------------------------------------------------------------------------------------------------

mat4x4 inverse(const mat4x4 &Matrix);
mat4x4 look(const vec3 &eye, const vec3 &center, const vec3 &up);
mat4x4 ortho(double left, double right, double bottom, double top, double n, double f);
mat4x4 perspective(double fovy, double aspect, double n, double f);
mat4x4 rotate(double angle, const vec3 &u);
mat4x4 scale(double x, double y, double z);
mat4x4 translate(double x, double y, double z);
mat4x4 transpose(const mat4x4 &Matrix);

#endif