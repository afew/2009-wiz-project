//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	Math Library.
//
//	Operator Overriding
//	Dot Product: '*'
//	Cross Product: '^'
//
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Math_H_
#define _DGE_Math_H_

#include <math.h>
#include <DGE_Type.h>


enum
{
	FIXED_PRECISION	=	(16),
	FIXED_ONE		=	(1 << FIXED_PRECISION),
	FIXED_ZERO		=	(0),
};

#define DGX_PI			3.1415926535897932384626433832795F
#define ONE_RADtoDEG	57.295779513082321F
#define ONE_DEGtoRAD	0.0174532925199433F
#define DEG90toRAD		1.5707963267948966F
#define DGXToRadian(d)	((d) * DGX_PI / 180.0F)
#define DGXToDegree(r)	((r) * 180.0F / DGX_PI)
#define RADtoDEG(v)		( (v)*ONE_RADtoDEG)
#define DEGtoRAD(v)		( (v)*ONE_DEGtoRAD)

#define DGX_ROUNDING_DELTA	0.00076f
#define TOLER				0.00076f
#define IS_EQ(a, b)			(fabs(a-b) < TOLER ? (TRUE) : (FALSE))

DGE_INLINE BOOL IsEqual(FLOAT a, FLOAT b)	{	return (fabs(a-b) < TOLER ? TRUE:FALSE);	}
DGE_INLINE BOOL IsNotEqual(FLOAT a, FLOAT b){	return (fabs(a-b) >= TOLER ? TRUE:FALSE);	}


DGE_INLINE GFIXED Fixed(INT    v)			{	return v<< FIXED_PRECISION;			}
DGE_INLINE GFIXED Fixed(FLOAT  v)			{	return GFIXED(v * 65536.F);			}
DGE_INLINE GFIXED Fixed(DOUBLE v)			{	return GFIXED(v * 65536.);			}
DGE_INLINE FLOAT  FloatFromFixed(GFIXED v)	{	return (FLOAT)v/(FLOAT)(FIXED_ONE);	}
DGE_INLINE INT	  IntFromFixed(GFIXED v)	{	return v>> FIXED_PRECISION;			}
DGE_INLINE FLOAT  FloatCutFixed(FLOAT v)	{	return FloatFromFixed(Fixed(v));	}


DGE_INLINE GFIXED DGE_FixedMultiply(GFIXED v1, GFIXED v2)
{
#if defined(_WIN32) || defined(WIN32)
	return GFIXED
		(
			((__int64)v1 * (__int64)v2) >> FIXED_PRECISION
		);
#else
	return GFIXED
		(
			(v1 * v2) >> FIXED_PRECISION
		);
#endif
}

DGE_INLINE int DGE_Quantum2Power(int v)
{
	int t=v, n=0;
	for(; t >>= 1 ;++n){};
	if( v ^ 1<<n)
		n++;

	return 1<<n;
}


////////////////////////////////////////////////////////////////////////////////
// Short Int type vector
// vector2 x=0, y=0
struct DGXVEC2s : public DGE_SHORT2
{
	DGXVEC2s();
	DGXVEC2s(const DGXVEC2s&);
	DGXVEC2s(const SHORT*);
	DGXVEC2s(const DGXVEC2s*);
	DGXVEC2s(SHORT,SHORT);
	DGXVEC2s(const DGE_SHORT2&);


	// casting
	operator SHORT*();
	operator const SHORT*() const;
	SHORT& operator[](int n);

	// assignment operators
	DGXVEC2s& operator +=(const DGXVEC2s&);
	DGXVEC2s& operator -=(const DGXVEC2s&);
	DGXVEC2s& operator *=(SHORT)	;
	DGXVEC2s& operator /=(SHORT)	;

	// unary operators
	DGXVEC2s operator +() const		;
	DGXVEC2s operator -() const		;

	// binary operators
	DGXVEC2s operator +(const DGXVEC2s&) const;
	DGXVEC2s operator -(const DGXVEC2s&) const;
	DGXVEC2s operator *(SHORT) const	;
	DGXVEC2s operator /(SHORT) const	;
	friend DGXVEC2s operator *(SHORT, const DGXVEC2s&);

	BOOL operator ==(const DGXVEC2s&) const;
	BOOL operator !=(const DGXVEC2s&) const;
};


// short3 x=0, y=0, z=0
// pack 2byte
#if defined(_WIN32) || defined(WIN32)

	#pragma pack(push, 2)
	struct DGXVEC3s : public DGE_SHORT3
	{
		DGXVEC3s();
		DGXVEC3s(const DGXVEC3s&);
		DGXVEC3s(const SHORT*);
		DGXVEC3s(const DGXVEC3s*);
		DGXVEC3s(SHORT,SHORT,SHORT);
		DGXVEC3s(const DGE_SHORT3&);

		// casting
		operator SHORT*();
		operator const SHORT*() const;
		SHORT& operator[](int n);

		// assignment operators
		DGXVEC3s& operator +=(const DGXVEC3s&);
		DGXVEC3s& operator -=(const DGXVEC3s&);
		DGXVEC3s& operator *=(SHORT)	;
		DGXVEC3s& operator /=(SHORT)	;

		// unary operators
		DGXVEC3s operator +() const		;
		DGXVEC3s operator -() const		;

		// binary operators
		DGXVEC3s operator +(const DGXVEC3s&) const;
		DGXVEC3s operator -(const DGXVEC3s&) const;
		DGXVEC3s operator *(SHORT) const	;
		DGXVEC3s operator /(SHORT) const	;
		friend DGXVEC3s operator *(SHORT, const DGXVEC3s&);

		BOOL operator ==(const DGXVEC3s&) const;
		BOOL operator !=(const DGXVEC3s&) const;
	};
	#pragma pack(pop)

#else

	typedef struct tagDGXVEC3s : public tagDGE_SHORT3
	{
		tagDGXVEC3s();
		tagDGXVEC3s(const tagDGXVEC3s&);
		tagDGXVEC3s(const SHORT*);
		tagDGXVEC3s(const tagDGXVEC3s*);
		tagDGXVEC3s(SHORT,SHORT,SHORT);
		tagDGXVEC3s(const tagDGE_SHORT3&);

		// casting
		operator SHORT*();
		operator const SHORT*() const;
		SHORT& operator[](int n);

		// assignment operators
		tagDGXVEC3s& operator +=(const tagDGXVEC3s&);
		tagDGXVEC3s& operator -=(const tagDGXVEC3s&);
		tagDGXVEC3s& operator *=(SHORT)	;
		tagDGXVEC3s& operator /=(SHORT)	;

		// unary operators
		tagDGXVEC3s operator +() const		;
		tagDGXVEC3s operator -() const		;

		// binary operators
		tagDGXVEC3s operator +(const tagDGXVEC3s&) const;
		tagDGXVEC3s operator -(const tagDGXVEC3s&) const;
		tagDGXVEC3s operator *(SHORT) const	;
		tagDGXVEC3s operator /(SHORT) const	;
		friend tagDGXVEC3s operator *(SHORT, const tagDGXVEC3s&);

		BOOL operator ==(const tagDGXVEC3s&) const;
		BOOL operator !=(const tagDGXVEC3s&) const;
	} __attribute__((packed)) tagDGXVEC3s;
	
#endif




// Colors Byte. color range [0, 255]
// Color r = 255, g = 255, b = 255, a = 255
struct DGXCOLORb : public DGE_COLORB
{
	DGXCOLORb();
	DGXCOLORb(const DGXCOLORb&);
	DGXCOLORb(const BYTE*);
	DGXCOLORb(BYTE R, BYTE G, BYTE B, BYTE A);
	DGXCOLORb(DWORD argb);		// Need ARGB 32 bit
	DGXCOLORb(const DGE_COLORB&);

	// casting
	operator DWORD () const;
	operator BYTE* ();
	operator const BYTE* () const;
	BYTE& operator[](int n);


	// assignment operators
	DGXCOLORb& operator +=(const DGXCOLORb&);
	DGXCOLORb& operator -=(const DGXCOLORb&);
	DGXCOLORb& operator *=(const DGXCOLORb&);
	DGXCOLORb& operator *=(BYTE)	;
	DGXCOLORb& operator /=(BYTE)	;

	// unary operators
	DGXCOLORb operator +() const	;
	DGXCOLORb operator -() const	;

	// binary operators
	DGXCOLORb operator+ (const DGXCOLORb&) const;
	DGXCOLORb operator- (const DGXCOLORb&) const;
	DGXCOLORb operator* (const DGXCOLORb&) const;
	DGXCOLORb operator* (BYTE) const			;
	DGXCOLORb operator/ (BYTE) const			;
	friend DGXCOLORb operator* (BYTE, const DGXCOLORb&);

	BOOL operator == (const DGXCOLORb&) const	;
	BOOL operator != (const DGXCOLORb&) const	;
};


////////////////////////////////////////////////////////////////////////////////
// INT type vector

// vector2 x=0, y=0
struct DGXVEC2i : public DGE_INT2
{
	DGXVEC2i();
	DGXVEC2i(const DGXVEC2i&);
	DGXVEC2i(const INT*);
	DGXVEC2i(const DGXVEC2i*);
	DGXVEC2i(INT,INT);
	DGXVEC2i(FLOAT,FLOAT);
	DGXVEC2i(const FLOAT*);
	DGXVEC2i(const DGE_INT2&);

	// casting
	operator INT*();
	operator const INT*() const;
	INT& operator[](int n);
	const DGXVEC2i& operator=(const DGXVEC2i&);

	// assignment operators
	DGXVEC2i& operator +=(const DGXVEC2i&);
	DGXVEC2i& operator -=(const DGXVEC2i&);
	DGXVEC2i& operator *=(INT)	;
	DGXVEC2i& operator /=(INT)	;

	// unary operators
	DGXVEC2i operator +() const	;
	DGXVEC2i operator -() const	;

	// binary operators
	DGXVEC2i operator +(const DGXVEC2i&) const;
	DGXVEC2i operator -(const DGXVEC2i&) const;
	DGXVEC2i operator *(INT) const;
	DGXVEC2i operator /(INT) const;
	friend DGXVEC2i operator* (INT, const DGXVEC2i&);

	BOOL operator ==(const DGXVEC2i&) const;
	BOOL operator !=(const DGXVEC2i&) const;
};

// vector3 x=0, y=0, z=0
struct DGXVEC3i : public DGE_INT3
{
	DGXVEC3i();
	DGXVEC3i(const DGXVEC3i&);
	DGXVEC3i(const INT*);
	DGXVEC3i(const DGXVEC3i*);
	DGXVEC3i(INT,INT,INT);
	DGXVEC3i(FLOAT,FLOAT,FLOAT);
	DGXVEC3i(const FLOAT*);
	DGXVEC3i(const DGE_INT3&);
	
	// casting
	operator INT*();
	operator const INT*() const;
	INT& operator[](int n);
	const DGXVEC3i& operator=(const DGXVEC3i&);

	// assignment operators
	DGXVEC3i& operator +=(const DGXVEC3i&);
	DGXVEC3i& operator -=(const DGXVEC3i&);
	DGXVEC3i& operator *=(INT)	;
	DGXVEC3i& operator /=(INT)	;

	// unary operators
	DGXVEC3i operator +() const	;
	DGXVEC3i operator -() const	;

	// binary operators
	DGXVEC3i operator +(const DGXVEC3i&) const;
	DGXVEC3i operator -(const DGXVEC3i&) const;
	DGXVEC3i operator *(INT) const		;
	DGXVEC3i operator /(INT) const		;
	friend DGXVEC3i operator*(INT f,const DGXVEC3i& v);

	BOOL operator==(const DGXVEC3i&) const;
	BOOL operator!=(const DGXVEC3i&) const;
};


// vector4 x=0, y=0, z=0, w=0
struct DGXVEC4i : public DGE_INT4
{
	DGXVEC4i();
	DGXVEC4i(const DGXVEC4i& r);
	DGXVEC4i(const INT*);
	DGXVEC4i(const DGXVEC4i*);
	DGXVEC4i(INT,INT,INT,INT);
	DGXVEC4i(FLOAT,FLOAT,FLOAT,FLOAT);
	DGXVEC4i(const DGE_INT4&);

	// casting
	operator INT*();
	operator const INT*() const;
	INT& operator[](int n);
	const DGXVEC4i& operator=(const DGXVEC4i&);

	// assignment operators
	DGXVEC4i& operator +=(const DGXVEC4i&);
	DGXVEC4i& operator -=(const DGXVEC4i&);
	DGXVEC4i& operator *=(INT)	;
	DGXVEC4i& operator /=(INT)	;
	
	// unary operators
	DGXVEC4i operator +() const	;
	DGXVEC4i operator -() const	;
	
	// binary operators
	DGXVEC4i operator +(const DGXVEC4i&) const;
	DGXVEC4i operator -(const DGXVEC4i&) const;
	DGXVEC4i operator *(INT) const	;
	DGXVEC4i operator /(INT) const	;
	friend DGXVEC4i operator*(INT, const DGXVEC4i&);

	BOOL operator==(const DGXVEC4i& v) const;
	BOOL operator!=(const DGXVEC4i& v) const;
};


////////////////////////////////////////////////////////////////////////////////
// FLOAT type vector

// vector2 x=0, y=0
struct DGXVECTOR2 : public DGE_FLOAT2
{
	DGXVECTOR2();
	DGXVECTOR2(const DGXVECTOR2&);
	DGXVECTOR2(const FLOAT*);
	DGXVECTOR2(const DGXVECTOR2*);
	DGXVECTOR2(FLOAT,FLOAT);
	DGXVECTOR2(const DGE_FLOAT2&);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// assignment operators
	DGXVECTOR2& operator +=(const DGXVECTOR2&);
	DGXVECTOR2& operator -=(const DGXVECTOR2&);
	DGXVECTOR2& operator *=(FLOAT);
	DGXVECTOR2& operator /=(FLOAT);

	// unary operators
	DGXVECTOR2 operator +() const;
	DGXVECTOR2 operator -() const;

	// binary operators
	DGXVECTOR2 operator +(const DGXVECTOR2&) const;
	DGXVECTOR2 operator -(const DGXVECTOR2&) const;
	DGXVECTOR2 operator *(FLOAT) const;
	DGXVECTOR2 operator /(FLOAT) const;
	friend DGXVECTOR2 operator *(FLOAT, const DGXVECTOR2&);

	BOOL operator ==(const DGXVECTOR2&) const;
	BOOL operator !=(const DGXVECTOR2&) const;

	// Dot Product
	FLOAT operator *(const DGXVECTOR2&);
	friend FLOAT operator *(const DGXVECTOR2&, const DGXVECTOR2&);

	// Cross Product(Z-Value)
	FLOAT operator ^(const DGXVECTOR2&);
	friend FLOAT operator ^(const DGXVECTOR2&, const DGXVECTOR2&);

	// Transform: vector * Matrix4x4
	DGXVECTOR2 operator *(const FLOAT*);
	// Transform: Matrix4x4 * vector;
	friend DGXVECTOR2 operator *(const FLOAT*, const DGXVECTOR2&);

	FLOAT		Length();						// Length
	FLOAT		LengthSq();						// Length Square
	DGXVECTOR2	Normalize();					// Magnitude = 1
	DGXVECTOR2	Normalize(const DGXVECTOR2*);	// Copy and Normalize
};


// vector3 x=0, y=0, z=0
struct DGXVECTOR3 : public DGE_FLOAT3
{
	DGXVECTOR3();
	DGXVECTOR3(const DGXVECTOR3&);
	DGXVECTOR3(const FLOAT*);
	DGXVECTOR3(const DGXVECTOR3*);
	DGXVECTOR3(FLOAT,FLOAT,FLOAT);
	DGXVECTOR3(const DGE_FLOAT3&);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// assignment operators
	DGXVECTOR3& operator +=(const DGXVECTOR3&);
	DGXVECTOR3& operator -=(const DGXVECTOR3&);
	DGXVECTOR3& operator *=(FLOAT);
	DGXVECTOR3& operator /=(FLOAT);

	// unary operators
	DGXVECTOR3 operator +() const;
	DGXVECTOR3 operator -() const;

	// binary operators
	DGXVECTOR3 operator +(const DGXVECTOR3&) const;
	DGXVECTOR3 operator -(const DGXVECTOR3&) const;
	DGXVECTOR3 operator *(FLOAT) const;
	DGXVECTOR3 operator /(FLOAT) const;
	friend DGXVECTOR3 operator *(FLOAT, const DGXVECTOR3&);

	BOOL operator ==(const DGXVECTOR3&) const;
	BOOL operator !=(const DGXVECTOR3&) const;

	// Dot Product
	FLOAT operator *(const DGXVECTOR3&);
	friend FLOAT operator *(const DGXVECTOR3&, const DGXVECTOR3&);

	// Cross Product
	DGXVECTOR3 operator ^(const DGXVECTOR3&);
	friend DGXVECTOR3 operator ^(const DGXVECTOR3&, const DGXVECTOR3&);

	// Transform: vector * Matrix4x4
	DGXVECTOR3 operator *(const FLOAT*);

	// Transform: Matrix4x4 * vector;
	friend DGXVECTOR3 operator *(const FLOAT*, const DGXVECTOR3&);

	FLOAT		Length();						// Length
	FLOAT		LengthSq();						// Length Square
	DGXVECTOR3	Normalize();					// Magnitude = 1
	DGXVECTOR3	Normalize(const DGXVECTOR3*);	// Copy and Normalize
	DGXVECTOR3	Cross(const DGXVECTOR3*, const DGXVECTOR3*);	// this = A x B
};


// vector4 x=0, y=0, z=0, w=0
struct DGXVECTOR4 : public DGE_FLOAT4
{
	DGXVECTOR4();
	DGXVECTOR4(const DGXVECTOR4&);
	DGXVECTOR4(const FLOAT*);
	DGXVECTOR4(const DGXVECTOR4*);
	DGXVECTOR4(FLOAT,FLOAT,FLOAT,FLOAT);
	DGXVECTOR4(const DGE_FLOAT4& v);

	// casting
	operator FLOAT*();
	operator const FLOAT*() const;
	FLOAT& operator[](int n);

	// assignment operators
	DGXVECTOR4& operator +=(const DGXVECTOR4&);
	DGXVECTOR4& operator -=(const DGXVECTOR4&);
	DGXVECTOR4& operator *=(FLOAT v);
	DGXVECTOR4& operator /=(FLOAT v);

	// unary operators
	DGXVECTOR4 operator +() const;
	DGXVECTOR4 operator -() const;

	// binary operators
	DGXVECTOR4 operator +(const DGXVECTOR4&) const;
	DGXVECTOR4 operator -(const DGXVECTOR4&) const;
	DGXVECTOR4 operator *(FLOAT) const;
	DGXVECTOR4 operator /(FLOAT) const;
	friend DGXVECTOR4 operator *(FLOAT, const DGXVECTOR4&);

	BOOL operator ==(const DGXVECTOR4&) const;
	BOOL operator !=(const DGXVECTOR4&) const;

	// Dot Product
	FLOAT operator *(const DGXVECTOR4&);
	friend FLOAT operator *(const DGXVECTOR4&, const DGXVECTOR4&);

	// Transform: vector * Matrix4x4
	DGXVECTOR4 operator *(const FLOAT*);

	// Transform: Matrix4x4 * vector;
	friend DGXVECTOR4 operator *(const FLOAT*, const DGXVECTOR4&);

	FLOAT		Length();						// Length
	FLOAT		LengthSq();						// Length Square
	DGXVECTOR4	Normalize();					// Magnitude = 1
	DGXVECTOR4	Normalize(const DGXVECTOR4*);	// Copy and Normalize
};



////////////////////////////////////////////////////////////////////////////////
// Matrix4x4 ==> Identity Matrix

struct DGXMATRIX : public DGE_MATRIX
{
	DGXMATRIX();
	DGXMATRIX(const DGXMATRIX&);
	DGXMATRIX(const FLOAT*);
	DGXMATRIX(const DGXMATRIX*);
	DGXMATRIX(	FLOAT _11,FLOAT _12,FLOAT _13,FLOAT _14,
				FLOAT _21,FLOAT _22,FLOAT _23,FLOAT _24,
				FLOAT _31,FLOAT _32,FLOAT _33,FLOAT _34,
				FLOAT _41,FLOAT _42,FLOAT _43,FLOAT _44 );

	DGXMATRIX(const DGE_MATRIX&);

	// access grants
	FLOAT& operator () ( int iRow, int iCol );
	FLOAT  operator () ( int iRow, int iCol ) const;

	// casting operators
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	DGXMATRIX& operator *=(const DGXMATRIX&);
	DGXMATRIX& operator +=(const DGXMATRIX&);
	DGXMATRIX& operator -=(const DGXMATRIX&);
	DGXMATRIX& operator *=(FLOAT);
	DGXMATRIX& operator /=(FLOAT);

	// unary operators
	DGXMATRIX operator +() const;
	DGXMATRIX operator -() const;

	DGXMATRIX operator *(const DGXMATRIX&) const;
	DGXMATRIX operator +(const DGXMATRIX&) const;
	DGXMATRIX operator -(const DGXMATRIX&) const;
	DGXMATRIX operator *(FLOAT) const;
	DGXMATRIX operator /(FLOAT) const;

	// const * Matrix
	friend DGXMATRIX operator *(FLOAT, const DGXMATRIX&);
	friend DGXMATRIX operator *(const DGXMATRIX&, FLOAT);

	BOOL operator ==(const DGXMATRIX&) const;
	BOOL operator !=(const DGXMATRIX&) const;

	DGXMATRIX&	Identity();
	DGXMATRIX&	Transpose();
	DGXMATRIX&	Transpose(const DGXMATRIX*);
	DGXMATRIX&	Inverse(INT bQuick=TRUE);						// Quick: _14=0, _24=0, _34=0, _44=1 이면 3X3만 계산
	DGXMATRIX&	Inverse(const DGXMATRIX* v, INT bQuick=TRUE);	//
	FLOAT		Determinant();

	DGXMATRIX&	SetupScaling(FLOAT X, FLOAT Y, FLOAT Z);
	DGXMATRIX&	SetupViewLH(const DGXVECTOR3* vEye, const DGXVECTOR3* vLook, const DGXVECTOR3* vUp );	// Left Handle
	DGXMATRIX&	SetupViewRH(const DGXVECTOR3* vEye, const DGXVECTOR3* vLook, const DGXVECTOR3* vUp );	// Right Handle
	DGXMATRIX&	SetupPerspectiveLH(FLOAT fFOV, FLOAT fAspect, FLOAT fNear, FLOAT fFar);	// x,y: [-1, 1], z: [0, 1]
	DGXMATRIX&	SetupPerspectiveRH(FLOAT fFOV, FLOAT fAspect, FLOAT fNear, FLOAT fFar);	// Right Handle
	DGXMATRIX&	SetupRotationX(FLOAT fRad);
	DGXMATRIX&	SetupRotationY(FLOAT fRad);
	DGXMATRIX&	SetupRotationZ(FLOAT fRad);
	DGXMATRIX&	SetupRotationAxis(const DGXVECTOR3* vAxis, FLOAT fRad);
	DGXMATRIX&	SetupTranslation(const DGXVECTOR3* vTrs, BOOL bIdentity=TRUE);

	void		TransformCoord(DGXVECTOR3* pOut, const DGXVECTOR3* pIn);
};



////////////////////////////////////////////////////////////////////////////////
// Quaternion: x=0, y=0, z=0, w=1
struct DGXQUATERNION : public DGE_FLOAT4
{
	DGXQUATERNION();
	DGXQUATERNION(const DGXQUATERNION&);
	DGXQUATERNION(const FLOAT*);
	DGXQUATERNION(const DGXQUATERNION*);
	DGXQUATERNION(FLOAT x,FLOAT y,FLOAT z,FLOAT w);
	DGXQUATERNION(const DGE_FLOAT4&);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	DGXQUATERNION& operator +=(const DGXQUATERNION&);
	DGXQUATERNION& operator -=(const DGXQUATERNION&);
	DGXQUATERNION& operator *=(const DGXQUATERNION&);
	DGXQUATERNION& operator *=(FLOAT);
	DGXQUATERNION& operator /=(FLOAT);

	// unary operators
	DGXQUATERNION  operator +() const;
	DGXQUATERNION  operator -() const;

	// binary operators
	DGXQUATERNION operator +(const DGXQUATERNION&) const;
	DGXQUATERNION operator -(const DGXQUATERNION&) const;
	DGXQUATERNION operator *(const DGXQUATERNION&) const;
	DGXQUATERNION operator *(FLOAT) const;
	DGXQUATERNION operator /(FLOAT) const;
	friend DGXQUATERNION operator *(FLOAT,const DGXQUATERNION&);

	BOOL operator ==(const DGXQUATERNION&) const;
	BOOL operator !=(const DGXQUATERNION&) const;

	//Q = (1/sinθ)[  sin (θ*(1-t)) * Q1 + sin (θ*t) * Q2]
	void SLerp(const DGXQUATERNION* q1, const DGXQUATERNION* q2, FLOAT t);
	void RotationMatrix(DGXMATRIX* pOut, BOOL bDX = TRUE);
};


////////////////////////////////////////////////////////////////////////////////
// Colors r=1.0F, g=1.0F, b=1.0F, a=1.0F
struct DGXCOLOR : DGE_COLORF
{
	DGXCOLOR();
	DGXCOLOR(const DGXCOLOR&);
	DGXCOLOR(const FLOAT *);
	DGXCOLOR(const DGXCOLOR*);
	DGXCOLOR(DWORD argb);
	DGXCOLOR(const BYTE* rgba/*r[0],g[1],b[2],a[3]*/);
	DGXCOLOR(FLOAT r,FLOAT g,FLOAT b,FLOAT a);
	DGXCOLOR(const DGE_COLORF&);

	// casting
	operator DWORD () const;
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// assignment operators
	DGXCOLOR& operator +=(const DGXCOLOR&);
	DGXCOLOR& operator -=(const DGXCOLOR&);
	DGXCOLOR& operator *=(FLOAT);
	DGXCOLOR& operator /=(FLOAT);

	// unary operators
	DGXCOLOR operator +() const;
	DGXCOLOR operator -() const;

	// binary operators
	DGXCOLOR operator +(const DGXCOLOR&) const;
	DGXCOLOR operator -(const DGXCOLOR&) const;
	DGXCOLOR operator *(FLOAT) const;
	DGXCOLOR operator /(FLOAT) const;
	friend DGXCOLOR operator *(FLOAT,const DGXCOLOR&);

	BOOL operator == (const DGXCOLOR&) const;
	BOOL operator != (const DGXCOLOR&) const;
};


////////////////////////////////////////////////////////////////////////////////
// Plane
struct DGXPLANE
{
	union {	struct { FLOAT a; FLOAT b; FLOAT c;	 FLOAT d; }; FLOAT m[4]; };

	DGXPLANE();
	DGXPLANE(const DGXPLANE&);
	DGXPLANE(const FLOAT*);
	DGXPLANE(FLOAT a,FLOAT b,FLOAT c,FLOAT d);

	// casting
	operator FLOAT* ();
	operator const FLOAT* () const;
	FLOAT& operator[](int n);

	// unary operators
	DGXPLANE operator + () const;
	DGXPLANE operator - () const;

	// binary operators
	BOOL operator == ( const DGXPLANE& ) const;
	BOOL operator != ( const DGXPLANE& ) const;

	void SetupFromPointNormal(const DGXVECTOR3* point, const DGXVECTOR3* normal);
	void SetupFromPoints(const DGXVECTOR3* p0, const DGXVECTOR3* p1, const DGXVECTOR3* p2);
};


FLOAT DGXVec3Dot(const DGXVECTOR3* p1, const DGXVECTOR3* p2);
FLOAT DGXVec3Length(const DGXVECTOR3* v);
FLOAT DGXPlaneDotCoord(const DGXPLANE *pP, const DGXVECTOR3 *pV);



#endif	//_DGE_Math_H_



