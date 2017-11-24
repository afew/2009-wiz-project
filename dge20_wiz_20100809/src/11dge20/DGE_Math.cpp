// Implementation of the DGX Math Library.
//
////////////////////////////////////////////////////////////////////////////////


#include <math.h>

#include "DGE_Math.h"


////////////////////////////////////////////////////////////////////////////////
//  Short Int type vector

DGXVEC2s::DGXVEC2s()					{	x=0; y=0;		}
DGXVEC2s::DGXVEC2s(const DGXVEC2s& v)	{	x=v.x;	y=v.y;	}
DGXVEC2s::DGXVEC2s(const SHORT* v)		{	if(!v) return;	x=v[0]; y=v[1];	}
DGXVEC2s::DGXVEC2s(const DGXVEC2s* v)	{	if(!v) return;	x=v->x; y=v->y;	}
DGXVEC2s::DGXVEC2s(SHORT X, SHORT Y)	{	x=X; y=Y;		}
DGXVEC2s::DGXVEC2s(const DGE_SHORT2& v)	{	x=v.x; y=v.y;	}

// casting
DGXVEC2s::operator SHORT*()				{	return(SHORT*)&x;		}
DGXVEC2s::operator const SHORT*() const	{	return(const SHORT*)&x;	}
SHORT& DGXVEC2s::operator[](int n)		{	return *((&x)+ n);		}

// assignment operators
DGXVEC2s& DGXVEC2s::operator +=(const DGXVEC2s& v)	{	x += v.x; y += v.y;	return *this;	}
DGXVEC2s& DGXVEC2s::operator -=(const DGXVEC2s& v)	{	x -= v.x; y -= v.y;	return *this;	}
DGXVEC2s& DGXVEC2s::operator *=(SHORT v)			{	x *= v;	y *= v;		return *this;	}
DGXVEC2s& DGXVEC2s::operator /=(SHORT v)			{	x /= v;	y /= v;		return *this;	}

// unary operators
DGXVEC2s DGXVEC2s::operator +() const				{	return *this;						}
DGXVEC2s DGXVEC2s::operator -() const				{	return DGXVEC2s(-x, -y);			}

// binary operators
DGXVEC2s DGXVEC2s::operator +(const DGXVEC2s& v) const{	return DGXVEC2s(x + v.x, y + v.y);	}
DGXVEC2s DGXVEC2s::operator -(const DGXVEC2s& v) const{	return DGXVEC2s(x - v.x, y - v.y);	}
DGXVEC2s DGXVEC2s::operator *(SHORT v) const		{	return DGXVEC2s(x * v  , y * v  );	}
DGXVEC2s DGXVEC2s::operator /(SHORT v) const		{ 	return DGXVEC2s(x / v  , y / v  );	}
DGXVEC2s operator *(SHORT f, const DGXVEC2s& v)		{	return DGXVEC2s(f * v.x, f * v.y);	}

BOOL DGXVEC2s::operator ==(const DGXVEC2s& v) const	{	return x == v.x && y == v.y;		}
BOOL DGXVEC2s::operator !=(const DGXVEC2s& v) const	{	return x != v.x || y != v.y;		}


////////////////////////////////////////////////////////////////////////////////
#if defined(_WIN32) || defined(WIN32)
	DGXVEC3s::DGXVEC3s()					{	x=0; y=0; z=0;			}
	DGXVEC3s::DGXVEC3s(const DGXVEC3s& v)	{	x=v.x; y=v.y; z=v.z;	}
	DGXVEC3s::DGXVEC3s(const SHORT* v)		{	if(!v) return;	x=v[0];	y=v[1];	z=v[2];	}
	DGXVEC3s::DGXVEC3s(const DGXVEC3s* v)	{	if(!v) return;	x=v->x;	y=v->y;	z=v->z;	}
	DGXVEC3s::DGXVEC3s(SHORT X,SHORT Y,SHORT Z){	x=X; y=Y; z=Z;		}
	DGXVEC3s::DGXVEC3s(const DGE_SHORT3& v)	{	x=v.x; y=v.y; z=v.z;	}


	// casting
	DGXVEC3s::operator SHORT*()				{	return(SHORT*)&x;		}
	DGXVEC3s::operator const SHORT*() const	{	return(const SHORT*)&x;	}
	SHORT& DGXVEC3s::operator[](int n)		{	return *((&x)+ n);		}

	// assignment operators
	DGXVEC3s& DGXVEC3s::operator +=(const DGXVEC3s& v)	{	x += v.x; y += v.y; z += v.z;	return *this;	}
	DGXVEC3s& DGXVEC3s::operator -=(const DGXVEC3s& v)	{	x -= v.x; y -= v.y; z -= v.z;	return *this;	}
	DGXVEC3s& DGXVEC3s::operator *=(SHORT v)			{	x *= v;	y *= v;	z *= v;			return *this;	}
	DGXVEC3s& DGXVEC3s::operator /=(SHORT v)			{	x /= v;	y /= v;	z /= v;			return *this;	}

	// unary operators
	DGXVEC3s DGXVEC3s::operator +() const				{	return *this;									}
	DGXVEC3s DGXVEC3s::operator -() const				{	return DGXVEC3s(-x, -y, -z);					}

	// binary operators
	DGXVEC3s DGXVEC3s::operator +(const DGXVEC3s& v) const{	return DGXVEC3s(x + v.x, y + v.y, z + v.z);		}
	DGXVEC3s DGXVEC3s::operator -(const DGXVEC3s& v) const{	return DGXVEC3s(x - v.x, y - v.y, z - v.z);		}
	DGXVEC3s DGXVEC3s::operator *(SHORT v) const		{	return DGXVEC3s(x * v  , y * v  , z * v  );		}
	DGXVEC3s DGXVEC3s::operator /(SHORT v) const		{ 	return DGXVEC3s(x / v  , y / v  , z / v  );		}
	DGXVEC3s operator *(SHORT f, const DGXVEC3s& v)		{	return DGXVEC3s(f * v.x, f * v.y, f * v.z);		}

	BOOL DGXVEC3s::operator ==(const DGXVEC3s& v) const	{	return x == v.x && y == v.y && z == v.z;		}
	BOOL DGXVEC3s::operator !=(const DGXVEC3s& v) const	{	return x != v.x || y != v.y || z != v.z;		}
#else
	tagDGXVEC3s::tagDGXVEC3s()					{	x=0; y=0; z=0;			}
	tagDGXVEC3s::tagDGXVEC3s(const tagDGXVEC3s& v)	{	x=v.x; y=v.y; z=v.z;	}
	tagDGXVEC3s::tagDGXVEC3s(const SHORT* v)		{	if(!v) return;	x=v[0];	y=v[1];	z=v[2];	}
	tagDGXVEC3s::tagDGXVEC3s(const tagDGXVEC3s* v)	{	if(!v) return;	x=v->x;	y=v->y;	z=v->z;	}
	tagDGXVEC3s::tagDGXVEC3s(SHORT X,SHORT Y,SHORT Z){	x=X; y=Y; z=Z;		}
	tagDGXVEC3s::tagDGXVEC3s(const tagDGE_SHORT3& v){	x=v.x; y=v.y; z=v.z;	}


	// casting
	tagDGXVEC3s::operator SHORT*()				{	return(SHORT*)&x;		}
	tagDGXVEC3s::operator const SHORT*() const	{	return(const SHORT*)&x;	}
	SHORT& tagDGXVEC3s::operator[](int n)		{	return *((&x)+ n);		}

	// assignment operators
	tagDGXVEC3s& tagDGXVEC3s::operator +=(const tagDGXVEC3s& v)	{	x += v.x; y += v.y; z += v.z;	return *this;	}
	tagDGXVEC3s& tagDGXVEC3s::operator -=(const tagDGXVEC3s& v)	{	x -= v.x; y -= v.y; z -= v.z;	return *this;	}
	tagDGXVEC3s& tagDGXVEC3s::operator *=(SHORT v)				{	x *= v;	y *= v;	z *= v;			return *this;	}
	tagDGXVEC3s& tagDGXVEC3s::operator /=(SHORT v)				{	x /= v;	y /= v;	z /= v;			return *this;	}

	// unary operators
	tagDGXVEC3s tagDGXVEC3s::operator +() const				{	return *this;									}
	tagDGXVEC3s tagDGXVEC3s::operator -() const				{	return tagDGXVEC3s(-x, -y, -z);					}

	// binary operators
	tagDGXVEC3s tagDGXVEC3s::operator +(const tagDGXVEC3s& v) const{return tagDGXVEC3s(x + v.x, y + v.y, z + v.z);		}
	tagDGXVEC3s tagDGXVEC3s::operator -(const tagDGXVEC3s& v) const{return tagDGXVEC3s(x - v.x, y - v.y, z - v.z);		}
	tagDGXVEC3s tagDGXVEC3s::operator *(SHORT v) const			{	return tagDGXVEC3s(x * v  , y * v  , z * v  );		}
	tagDGXVEC3s tagDGXVEC3s::operator /(SHORT v) const			{ 	return tagDGXVEC3s(x / v  , y / v  , z / v  );		}
	tagDGXVEC3s operator *(SHORT f, const tagDGXVEC3s& v)		{	return tagDGXVEC3s(f * v.x, f * v.y, f * v.z);		}

	BOOL tagDGXVEC3s::operator ==(const tagDGXVEC3s& v) const	{	return x == v.x && y == v.y && z == v.z;		}
	BOOL tagDGXVEC3s::operator !=(const tagDGXVEC3s& v) const	{	return x != v.x || y != v.y || z != v.z;		}
#endif



// Colors Byte
////////////////////////////////////////////////////////////////////////////////

DGXCOLORb::DGXCOLORb()						{ r=0xFF; g=0xFF; b=0xFF; a=0xFF;		}
DGXCOLORb::DGXCOLORb(const DGXCOLORb& v)	{	r=v.r; g=v.g; b=v.b; a=v.a;			}
DGXCOLORb::DGXCOLORb(const BYTE* v)			{	r=v[0]; g=v[1];	b=v[2];	a=v[3];		}
DGXCOLORb::DGXCOLORb(BYTE R,BYTE G,BYTE B,BYTE A){ r=R; g=G; b=B; a=A;				}
DGXCOLORb::DGXCOLORb(DWORD v)				{	r=(BYTE)(v>>16); g=(BYTE)(v>>8); b=(BYTE)(v>>0); a=(BYTE)(v>>24);	}
DGXCOLORb::DGXCOLORb(const DGE_COLORB& v)	{	r=v.r; g=v.g; b=v.b; a=v.a;			}

// casting
DGXCOLORb::operator DWORD () const		{	return (a<<24) | (r<<16) | (g<<8) | b;	}
DGXCOLORb::operator BYTE* ()			{	return (BYTE*) &r;						}
DGXCOLORb::operator const BYTE* () const{	return (const BYTE*) &r;				}
BYTE& DGXCOLORb::operator[](int n)		{	return *((&r)+ n);						}

// assignment operators
DGXCOLORb& DGXCOLORb::operator+= (const DGXCOLORb& v){	r += v.r;	g += v.g;	b += v.b;	a += v.a;	return *this;	}
DGXCOLORb& DGXCOLORb::operator-= (const DGXCOLORb& v){	r -= v.r;	g -= v.g;	b -= v.b;	a -= v.a;	return *this;	}
DGXCOLORb& DGXCOLORb::operator*= (const DGXCOLORb& v){	r *= v.r;	g *= v.g;	b *= v.b;	a *= v.a;	return *this;	}
DGXCOLORb& DGXCOLORb::operator*= (BYTE f)			{	r *= f;		g *= f;		b *= f;		a *= f;		return *this;	}
DGXCOLORb& DGXCOLORb::operator/= (BYTE f)			{	r /= f;		g /= f;		b /= f;		a /= f;		return *this;	}

// unary operators
DGXCOLORb DGXCOLORb::operator+ () const				{	return *this;						}
DGXCOLORb DGXCOLORb::operator- () const				{	return DGXCOLORb(-r, -g, -b, -a);	}

// binary operators
DGXCOLORb DGXCOLORb::operator+ (const DGXCOLORb& v)const{	return DGXCOLORb(r + v.r, g + v.g, b + v.b, a + v.a);	}
DGXCOLORb DGXCOLORb::operator- (const DGXCOLORb& v)const{	return DGXCOLORb(r - v.r, g - v.g, b - v.b, a - v.a);	}
DGXCOLORb DGXCOLORb::operator* (const DGXCOLORb& v)const{	return DGXCOLORb(r * v.r, g * v.g, b * v.b, a * v.a);	}
DGXCOLORb DGXCOLORb::operator* (BYTE f) const			{	return DGXCOLORb(r * f  , g * f  , b * f  , a * f  );	}
DGXCOLORb DGXCOLORb::operator/ (BYTE f) const			{	return DGXCOLORb(r / f  , g / f  , b / f  , a / f  );	}
DGXCOLORb operator* (BYTE f, const DGXCOLORb& v)		{	return DGXCOLORb(f * v.r, f * v.g, f * v.b, f * v.a);	}

BOOL DGXCOLORb::operator == (const DGXCOLORb& v) const	{	return r == v.r && g == v.g && b == v.b && a == v.a;	}
BOOL DGXCOLORb::operator != (const DGXCOLORb& v) const	{	return r != v.r || g != v.g || b != v.b || a != v.a;	}



// INT type vector
////////////////////////////////////////////////////////////////////////////////

DGXVEC2i::DGXVEC2i()					{	x=0; y=0;		}
DGXVEC2i::DGXVEC2i(const DGXVEC2i& v)	{	x=v.x; y=v.y;	}
DGXVEC2i::DGXVEC2i(const INT* v)	{	if(!v) return;	x=v[0]; y=v[1];	}
DGXVEC2i::DGXVEC2i(const DGXVEC2i* v){	if(!v) return;	x=v->x; y=v->y;	}
DGXVEC2i::DGXVEC2i(INT X, INT Y)		{	x=X; y=Y;		}
DGXVEC2i::DGXVEC2i(FLOAT X,FLOAT Y)		{	x=Fixed(X); y=Fixed(Y);		}
DGXVEC2i::DGXVEC2i(const FLOAT* v)		{	x=Fixed(v[0]); y=Fixed(v[1]);		}
DGXVEC2i::DGXVEC2i(const DGE_INT2& v)	{	x=v.x; y=v.y;						}
// casting
DGXVEC2i::operator INT*()			{	return(INT*)&x;			}
DGXVEC2i::operator const INT*() const{	return(const INT*)&x;	}
INT& DGXVEC2i::operator[](int n)	{	return *((&x)+ n);		}
const DGXVEC2i& DGXVEC2i::operator=(const DGXVEC2i& v) {	x=v.x; y=v.y; return *this;		}

// assignment operators
DGXVEC2i& DGXVEC2i::operator +=(const DGXVEC2i& v)	{	x += v.x; y += v.y;	return *this;	}
DGXVEC2i& DGXVEC2i::operator -=(const DGXVEC2i& v)	{	x -= v.x; y -= v.y;	return *this;	}
DGXVEC2i& DGXVEC2i::operator *=(INT v)				{	x *= v;	y *= v;		return *this;	}
DGXVEC2i& DGXVEC2i::operator /=(INT v)				{	x /= v;	y /= v;		return *this;	}

// unary operators
DGXVEC2i DGXVEC2i::operator +() const				{	return *this;						}
DGXVEC2i DGXVEC2i::operator -() const				{	return DGXVEC2i(-x, -y);			}

// binary operators
DGXVEC2i DGXVEC2i::operator +(const DGXVEC2i& v) const{	return DGXVEC2i(x + v.x, y + v.y);	}
DGXVEC2i DGXVEC2i::operator -(const DGXVEC2i& v) const{	return DGXVEC2i(x - v.x, y - v.y);	}
DGXVEC2i DGXVEC2i::operator *(INT v) const			{	return DGXVEC2i(x * v  , y * v  );	}
DGXVEC2i DGXVEC2i::operator /(INT v) const			{	return DGXVEC2i(x / v  , y / v  );	}
DGXVEC2i operator *(INT f, const DGXVEC2i& v)		{	return DGXVEC2i(f * v.x, f * v.y);	}

BOOL DGXVEC2i::operator ==(const DGXVEC2i& v) const	{	return x == v.x && y == v.y;		}
BOOL DGXVEC2i::operator !=(const DGXVEC2i& v) const	{	return x != v.x || y != v.y;		}


////////////////////////////////////////////////////////////////////////////////

DGXVEC3i::DGXVEC3i()					{	x=0; y=0; z=0;							}
DGXVEC3i::DGXVEC3i(const DGXVEC3i& v)	{	x=v.x; y=v.y; z=v.z;					}
DGXVEC3i::DGXVEC3i(const INT* v)		{	if(!v) return;	x=v[0]; y=v[1]; z=v[2];	}
DGXVEC3i::DGXVEC3i(const DGXVEC3i* v)	{	if(!v) return;	x=v->x; y=v->y; z=v->z;	}
DGXVEC3i::DGXVEC3i(INT X,INT Y,INT Z)	{	x=X; y=Y; z=Z;							}
DGXVEC3i::DGXVEC3i(FLOAT X,FLOAT Y,FLOAT Z){	x=Fixed(X); y=Fixed(Y); z=Fixed(Z);	}
DGXVEC3i::DGXVEC3i(const FLOAT* v)	{	x=Fixed(v[0]); y=Fixed(v[1]); z=Fixed(v[2]);}
DGXVEC3i::DGXVEC3i(const DGE_INT3& v)		{	x=v.x; y=v.y; z=v.z;				}

// casting
DGXVEC3i::operator INT*()					{	return(INT*)&x;								}
DGXVEC3i::operator const INT*() const		{	return(const INT*)&x;						}
INT& DGXVEC3i::operator[](int n)			{	return *((&x)+ n);							}
const DGXVEC3i& DGXVEC3i::operator=(const DGXVEC3i& v) { x=v.x;	y=v.y; z=v.z; return *this;	}

// assignment operators
DGXVEC3i& DGXVEC3i::operator +=(const DGXVEC3i& v)	{	x += v.x; y += v.y; z += v.z;	return *this;	}
DGXVEC3i& DGXVEC3i::operator -=(const DGXVEC3i& v)	{	x -= v.x; y -= v.y; z -= v.z;	return *this;	}
DGXVEC3i& DGXVEC3i::operator *=(INT v)				{	x *= v;	y *= v;	z *= v;			return *this;	}
DGXVEC3i& DGXVEC3i::operator /=(INT v)				{	x /= v;	y /= v;	z /= v;			return *this;	}

// unary operators
DGXVEC3i DGXVEC3i::operator +() const				{	return *this;									}
DGXVEC3i DGXVEC3i::operator -() const				{	return DGXVEC3i(-x, -y, -z);					}

// binary operators
DGXVEC3i DGXVEC3i::operator +(const DGXVEC3i& v) const{	return DGXVEC3i(x + v.x, y + v.y, z + v.z);		}
DGXVEC3i DGXVEC3i::operator -(const DGXVEC3i& v) const{	return DGXVEC3i(x - v.x, y - v.y, z - v.z);		}
DGXVEC3i DGXVEC3i::operator *(INT v) const			{	return DGXVEC3i(x * v  , y * v  , z * v  );		}
DGXVEC3i DGXVEC3i::operator /(INT v) const			{	return DGXVEC3i(x / v  , y / v  , z / v  );		}
DGXVEC3i operator *(INT f, const DGXVEC3i& v)		{	return DGXVEC3i(f * v.x, f * v.y, f * v.z);		}

BOOL DGXVEC3i::operator ==(const DGXVEC3i& v) const	{	return x == v.x && y == v.y && z == v.z;		}
BOOL DGXVEC3i::operator !=(const DGXVEC3i& v) const	{	return x != v.x || y != v.y || z != v.z;		}


////////////////////////////////////////////////////////////////////////////////

DGXVEC4i::DGXVEC4i()						{	x=0; y=0; z=0; w=0;					}
DGXVEC4i::DGXVEC4i(const DGXVEC4i& v)		{	x=v.x; y=v.y; z=v.z; w=v.w;			}
DGXVEC4i::DGXVEC4i(const INT* v)			{	if(!v) return;	x=v[0]; y=v[1]; z=v[2]; w=v[3];	}
DGXVEC4i::DGXVEC4i(const DGXVEC4i* v)		{	if(!v) return;	x=v->x; y=v->y; z=v->z; w=v->w;	}
DGXVEC4i::DGXVEC4i(INT X,INT Y,INT Z, INT W){	x=X; y=Y; z=Z; w=W;					}
DGXVEC4i::DGXVEC4i(FLOAT X,FLOAT Y,FLOAT Z,FLOAT W){x=Fixed(X); y=Fixed(Y); z=Fixed(Z); w=Fixed(W);	}
DGXVEC4i::DGXVEC4i(const DGE_INT4& v)		{	x=v.x; y=v.y; z=v.z; w=v.w;			}
// casting
DGXVEC4i::operator INT*()					{	return(INT*)&x;										}
DGXVEC4i::operator const INT*() const		{	return(const INT*)&x;								}
INT& DGXVEC4i::operator[](int n)			{	return *((&x)+ n);									}
const DGXVEC4i& DGXVEC4i::operator=(const DGXVEC4i& v) { x=v.x;	y=v.y; z=v.z; w=v.w; return *this;	}

// assignment operators
DGXVEC4i& DGXVEC4i::operator +=(const DGXVEC4i& v)	{	x+=v.x; y+=v.y; z+=v.z; w+=v.w;	return *this;	}
DGXVEC4i& DGXVEC4i::operator -=(const DGXVEC4i& v)	{	x-=v.x; y-=v.y; z-=v.z; w-=v.w;	return *this;	}
DGXVEC4i& DGXVEC4i::operator *=(INT v)				{	x *=v;	y *=v;	z *=v;	w *=v;	return *this;	}
DGXVEC4i& DGXVEC4i::operator /=(INT v)				{	x /=v;	y /=v;	z /=v;	w /=v;	return *this;	}

// unary operators
DGXVEC4i DGXVEC4i::operator +() const				{	return *this;									}
DGXVEC4i DGXVEC4i::operator -() const				{	return DGXVEC4i(-x, -y, -z, -w);				}

// binary operators
DGXVEC4i DGXVEC4i::operator +(const DGXVEC4i& v) const{	return DGXVEC4i(x+v.x, y+v.y, z+v.z, w+v.w);	}
DGXVEC4i DGXVEC4i::operator -(const DGXVEC4i& v) const{	return DGXVEC4i(x-v.x, y-v.y, z-v.z, w-v.w);	}
DGXVEC4i DGXVEC4i::operator *(INT v) const			{	return DGXVEC4i(x * v, y * v, z * v, w * v);	}
DGXVEC4i DGXVEC4i::operator /(INT v) const			{	return DGXVEC4i(x / v, y / v, z / v, w / v);	}
DGXVEC4i operator *(INT f, const DGXVEC4i& v)		{	return DGXVEC4i(f*v.x, f*v.y, f*v.z, f*v.w);	}

BOOL DGXVEC4i::operator ==(const DGXVEC4i& v) const	{	return x == v.x && y == v.y && z == v.z;		}
BOOL DGXVEC4i::operator !=(const DGXVEC4i& v) const	{	return x != v.x || y != v.y || z != v.z;		}




////////////////////////////////////////////////////////////////////////////////
// FLOAT type vector

DGXVECTOR2::DGXVECTOR2()					{	x=0.0F; y=0.0F;					}
DGXVECTOR2::DGXVECTOR2(const DGXVECTOR2& v)	{	x=v.x; y=v.y;					}
DGXVECTOR2::DGXVECTOR2(const FLOAT* v)		{	if(!v) return; x=v[0]; y=v[1];	}
DGXVECTOR2::DGXVECTOR2(const DGXVECTOR2* v)	{	if(!v) return; x=v->x; y=v->y;	}
DGXVECTOR2::DGXVECTOR2(FLOAT X, FLOAT Y)	{	x=X; y=Y;						}
DGXVECTOR2::DGXVECTOR2(const DGE_FLOAT2& v)	{	x=v.x; y=v.y;					}


// casting
DGXVECTOR2::operator FLOAT*()				{	return(FLOAT*)&x;		}
DGXVECTOR2::operator const FLOAT*() const	{	return(const FLOAT*)&x;	}
FLOAT& DGXVECTOR2::operator[](INT n)		{	return *((&x)+ n);		}

// assignment operators
DGXVECTOR2& DGXVECTOR2::operator +=(const DGXVECTOR2& v){	x += v.x;	y += v.y;	return *this;		}
DGXVECTOR2& DGXVECTOR2::operator -=(const DGXVECTOR2& v){	x -= v.x;	y -= v.y;	return *this;		}
DGXVECTOR2& DGXVECTOR2::operator *=(FLOAT v)			{	x *= v;		y *= v;		return *this;		}
DGXVECTOR2& DGXVECTOR2::operator /=(FLOAT v)			{	v = 1.0F/v;	x *= v;	y *= v;	return *this;	}

// unary operators
DGXVECTOR2 DGXVECTOR2::operator +() const		{	return *this;				}
DGXVECTOR2 DGXVECTOR2::operator -() const		{	return DGXVECTOR2(-x, -y);	}

// binary operators
DGXVECTOR2 DGXVECTOR2::operator +(const DGXVECTOR2& v) const	{	return DGXVECTOR2(x + v.x, y + v.y);	}
DGXVECTOR2 DGXVECTOR2::operator -(const DGXVECTOR2& v) const	{	return DGXVECTOR2(x - v.x, y - v.y);	}
DGXVECTOR2 DGXVECTOR2::operator *(FLOAT v) const				{	return DGXVECTOR2(x * v  , y * v  );	}
DGXVECTOR2 DGXVECTOR2::operator /(FLOAT v) const	{ v = 1.0F/v;	return DGXVECTOR2(x * v  , y * v  );	}
DGXVECTOR2 operator *(FLOAT f, const DGXVECTOR2& v)	{				return DGXVECTOR2(f * v.x, f * v.y);	}

//BOOL DGXVECTOR2::operator ==(const DGXVECTOR2& v) const	{	return x == v.x && y == v.y;			}
//BOOL DGXVECTOR2::operator !=(const DGXVECTOR2& v) const	{	return x != v.x || y != v.y;			}

BOOL DGXVECTOR2::operator ==(const DGXVECTOR2& v) const	{	return IsEqual(x, v.x)    && IsEqual(y, v.y);		}
BOOL DGXVECTOR2::operator !=(const DGXVECTOR2& v) const	{	return IsNotEqual(x, v.x) || IsNotEqual(y, v.y);	}


// Dot Product
FLOAT DGXVECTOR2::operator *(const DGXVECTOR2& v)			{	return x * v.x + y * v.y;			}
FLOAT operator *(const DGXVECTOR2& v1, const DGXVECTOR2& v2){	return v1.x * v2.x + v1.y * v2.y;	}

// Cross Product
FLOAT DGXVECTOR2::operator ^(const DGXVECTOR2& v)			{	return (   x * v.y  -    y * v.x );	}
FLOAT operator ^(const DGXVECTOR2& v1, const DGXVECTOR2& v2){	return (v1.x * v2.y - v1.y * v2.x);	}


// Transform: vector * Matrix
DGXVECTOR2 DGXVECTOR2::operator *(const FLOAT* v)
{
	FLOAT X = x * v[0] + y * v[4];
	FLOAT Y = x * v[1] + y * v[5];
	FLOAT W = x * v[3] + y * v[7];

	W = 1.0F/W;
	return DGXVECTOR2(X * W, Y * W);
}

// Transform: Matrix * vector;
DGXVECTOR2 operator *(const FLOAT* v1, const DGXVECTOR2& v2)
{
	FLOAT X = v2.x * v1[ 0] + v2.y * v1[ 1];
	FLOAT Y = v2.x * v1[ 4] + v2.y * v1[ 5];
	FLOAT W = v2.x * v1[12] + v2.y * v1[13];

	W = 1.0F/W;
	return DGXVECTOR2(X * W, Y * W);
}


FLOAT DGXVECTOR2::Length()			{	return (FLOAT)sqrt(x*x + y*y);		}
FLOAT DGXVECTOR2::LengthSq()		{	return(x*x + y*y);					}

DGXVECTOR2 DGXVECTOR2::Normalize()
{
	FLOAT l = this->Length();
	if(0.0F == l)
		return *this;

	l = 1.0F/l;
	x *= l;	y *= l;
	return *this;
}


DGXVECTOR2 DGXVECTOR2::Normalize(const DGXVECTOR2* v)
{
	*this = v;
	FLOAT l = this->Length();
	if(0.0F == l)
		return *this;

	l = 1.0F/l;
	x *= l;	y *= l;
	return *this;
}


////////////////////////////////////////////////////////////////////////////////

DGXVECTOR3::DGXVECTOR3()						{	x=0.0F; y=0.0F; z=0.0F;	}
DGXVECTOR3::DGXVECTOR3(const DGXVECTOR3& v)		{	x=v.x; y=v.y; z=v.z;	}
DGXVECTOR3::DGXVECTOR3(const FLOAT* v)		{	if(!v) return; x=v[0]; y=v[1]; z=v[2];	}
DGXVECTOR3::DGXVECTOR3(const DGXVECTOR3* v)	{	if(!v) return; x=v->x; y=v->y; z=v->z;	}
DGXVECTOR3::DGXVECTOR3(FLOAT X, FLOAT Y, FLOAT Z){	x=X;   y=Y;   z=Z;		}
DGXVECTOR3::DGXVECTOR3(const DGE_FLOAT3& v)		{	x=v.x; y=v.y; z=v.z;	}

// casting
DGXVECTOR3::operator FLOAT*()				{	return(FLOAT*)&x;			}
DGXVECTOR3::operator const FLOAT*() const	{	return(const FLOAT*)&x;		}
FLOAT& DGXVECTOR3::operator[](INT n)		{	return *((&x)+ n);			}

// assignment operators
DGXVECTOR3& DGXVECTOR3::operator +=(const DGXVECTOR3& v){	x +=v.x; y +=v.y; z +=v.z; return *this;	}
DGXVECTOR3& DGXVECTOR3::operator -=(const DGXVECTOR3& v){	x -=v.x; y -=v.y; z -=v.z; return *this;	}
DGXVECTOR3& DGXVECTOR3::operator *=(FLOAT v)			{	x *= v ; y *= v ; z *= v ; return *this;	}
DGXVECTOR3& DGXVECTOR3::operator /=(FLOAT v){	v = 1.0F/v;	x *= v ; y *= v ; z *= v ; return *this;	}

// unary operators
DGXVECTOR3 DGXVECTOR3::operator +() const	{	return *this;					}
DGXVECTOR3 DGXVECTOR3::operator -() const	{	return DGXVECTOR3(-x, -y, -z);	}

// binary operators
DGXVECTOR3 DGXVECTOR3::operator +(const DGXVECTOR3& v) const	{	return DGXVECTOR3(x + v.x, y + v.y, z + v.z);	}
DGXVECTOR3 DGXVECTOR3::operator -(const DGXVECTOR3& v) const	{	return DGXVECTOR3(x - v.x, y - v.y, z - v.z);	}
DGXVECTOR3 DGXVECTOR3::operator *(FLOAT v) const				{	return DGXVECTOR3(x * v  , y * v  , z * v  );	}
DGXVECTOR3 DGXVECTOR3::operator /(FLOAT v) const	{ v = 1.0F/v;	return DGXVECTOR3(x * v  , y * v  , z * v  );	}
DGXVECTOR3 operator *(FLOAT f, const DGXVECTOR3& v)	{				return DGXVECTOR3(f * v.x, f * v.y, f * v.z);	}

//BOOL DGXVECTOR3::operator ==(const DGXVECTOR3& v) const	{	return x == v.x && y == v.y && z == v.z;	}
//BOOL DGXVECTOR3::operator !=(const DGXVECTOR3& v) const	{	return x != v.x || y != v.y || z != v.z;	}

BOOL DGXVECTOR3::operator ==(const DGXVECTOR3& v) const	{	return IsEqual(x, v.x)    && IsEqual(y, v.y)    && IsEqual(z, v.z);		}
BOOL DGXVECTOR3::operator !=(const DGXVECTOR3& v) const	{	return IsNotEqual(x, v.x) || IsNotEqual(y, v.y) || IsNotEqual(z, v.z);	}

// Dot Product
FLOAT DGXVECTOR3::operator *(const DGXVECTOR3& v)			{	return x * v.x + y * v.y + z * v.z;				}
FLOAT operator *(const DGXVECTOR3& v1, const DGXVECTOR3& v2){	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;	}

// Cross Product
DGXVECTOR3 DGXVECTOR3::operator ^(const DGXVECTOR3& v)	
{
	return DGXVECTOR3(y * v.z  -  z * v.y
					, z * v.x  -  x * v.z
					, x * v.y  -  y * v.x	);
}


// Cross Product
DGXVECTOR3 operator ^(const DGXVECTOR3& v1, const DGXVECTOR3& v2)
{
	return DGXVECTOR3(v1.y * v2.z  -  v1.z * v2.y
					, v1.z * v2.x  -  v1.x * v2.z
					, v1.x * v2.y  -  v1.y * v2.x	);
}


// Transform: vector * Matrix
DGXVECTOR3 DGXVECTOR3::operator *(const FLOAT* v)
{
	FLOAT X = x * v[0] + y * v[4] + z * v[ 8] + v[12];
	FLOAT Y = x * v[1] + y * v[5] + z * v[ 9] + v[13];
	FLOAT Z = x * v[2] + y * v[6] + z * v[10] + v[14];
	FLOAT W = x * v[3] + y * v[7] + z * v[11] + v[15];

	W = 1.0F/W;
	return DGXVECTOR3(X * W, Y * W, Z* W);
}

// Transform: Matrix * vector;
DGXVECTOR3 operator *(const FLOAT* v1, const DGXVECTOR3& v2)
{
	FLOAT X = v2.x * v1[ 0] + v2.y * v1[ 1] + v2.z * v1[ 2] + v1[ 3];
	FLOAT Y = v2.x * v1[ 4] + v2.y * v1[ 5] + v2.z * v1[ 6] + v1[ 7];
	FLOAT Z = v2.x * v1[ 8] + v2.y * v1[ 9] + v2.z * v1[10] + v1[11];
	FLOAT W = v2.x * v1[12] + v2.y * v1[13] + v2.z * v1[14] + v1[15];

	W = 1.0F/W;
	return DGXVECTOR3(X * W, Y * W, Z* W);
}


FLOAT DGXVECTOR3::Length()	{	return (FLOAT)sqrt(x*x + y*y + z*z);	}
FLOAT DGXVECTOR3::LengthSq(){	return(x*x + y*y + z*z);				}

DGXVECTOR3 DGXVECTOR3::Normalize()
{
	FLOAT l = this->Length();
	if(0.0F == l)
		return *this;

	l = 1.0F/l;
	x *= l;	y *= l;	z *= l;
	return *this;
}


DGXVECTOR3 DGXVECTOR3::Normalize(const DGXVECTOR3* v)
{
	*this = v;
	FLOAT l = this->Length();
	if(l == 0)
		return *this;

	l = 1.0F/l;
	x *= l;	y *= l;	z *= l;
	return *this;
}


DGXVECTOR3 DGXVECTOR3::Cross(const DGXVECTOR3* v1, const DGXVECTOR3* v2)
{
	x  = (v1->y * v2->z  -  v1->z * v2->y);
	y  = (v1->z * v2->x  -  v1->x * v2->z);
	z  = (v1->x * v2->y  -  v1->y * v2->x);
	return *this;
}



////////////////////////////////////////////////////////////////////////////////

DGXVECTOR4::DGXVECTOR4()						{	x=0.0F; y=0.0F; z=0.0F; w=0.0F;	}
DGXVECTOR4::DGXVECTOR4(const DGXVECTOR4& v)		{	x=v.x; y=v.y; z=v.z; w=v.w;	}
DGXVECTOR4::DGXVECTOR4(const FLOAT* v)		{	if(!v) return; x=v[0]; y=v[1]; z=v[2]; w=v[3];	}
DGXVECTOR4::DGXVECTOR4(const DGXVECTOR4* v)	{	if(!v) return; x=v->x; y=v->y; z=v->z; w=v->w;	}
DGXVECTOR4::DGXVECTOR4(FLOAT X, FLOAT Y, FLOAT Z, FLOAT W){	x=X; y=Y; z=Z; w=W;	}
DGXVECTOR4::DGXVECTOR4(const DGE_FLOAT4& v)		{	x=v.x; y=v.y; z=v.z; w=v.w;	}

// casting
DGXVECTOR4::operator FLOAT*()				{	return(FLOAT*)&x;			}
DGXVECTOR4::operator const FLOAT*() const	{	return(const FLOAT*)&x;		}
FLOAT& DGXVECTOR4::operator[](INT n)		{	return *((&x)+ n);			}

// assignment operators
DGXVECTOR4& DGXVECTOR4::operator +=(const DGXVECTOR4& v){ x +=v.x; y +=v.y; z +=v.z; w +=v.w; return *this;	}
DGXVECTOR4& DGXVECTOR4::operator -=(const DGXVECTOR4& v){ x -=v.x; y -=v.y; z -=v.z; w -=v.w; return *this;	}
DGXVECTOR4& DGXVECTOR4::operator *=(FLOAT v)			{ x *= v;  y *=v;	z *=v;   w *= v;  return *this; }
DGXVECTOR4& DGXVECTOR4::operator /=(FLOAT v){	v = 1.0F/v; x*= v;  y *=v;   z *=v;   w *= v;  return *this;	}

// unary operators
DGXVECTOR4 DGXVECTOR4::operator +() const	{	return *this;						}
DGXVECTOR4 DGXVECTOR4::operator -() const	{	return DGXVECTOR4(-x,-y,-z,-w);		}

// binary operators
DGXVECTOR4 DGXVECTOR4::operator +(const DGXVECTOR4& v) const	{	return DGXVECTOR4(x + v.x, y + v.y, z + v.z, w + v.w);	}
DGXVECTOR4 DGXVECTOR4::operator -(const DGXVECTOR4& v) const	{	return DGXVECTOR4(x - v.x, y - v.y, z - v.z, w - v.w);	}
DGXVECTOR4 DGXVECTOR4::operator *(FLOAT v) const				{	return DGXVECTOR4(x * v  , y * v  , z * v  , w * v  );	}
DGXVECTOR4 DGXVECTOR4::operator /(FLOAT v) const	{ v = 1.0F/v;	return DGXVECTOR4(x * v  , y * v  , z * v  , w * v  );	}
DGXVECTOR4 operator *(FLOAT f, const DGXVECTOR4& v)	{				return DGXVECTOR4(f * v.x, f * v.y, f * v.z, f * v.w);	}

//BOOL DGXVECTOR4::operator ==(const DGXVECTOR4& v) const	{	return x == v.x && y == v.y && z == v.z && w == v.w;	}
//BOOL DGXVECTOR4::operator !=(const DGXVECTOR4& v) const	{	return x != v.x || y != v.y || z != v.z || w != v.w;	}

BOOL DGXVECTOR4::operator ==(const DGXVECTOR4& v) const	{	return IsEqual(x, v.x)    && IsEqual(y, v.y)    && IsEqual(z, v.z)    && IsEqual(w,v.w);	}
BOOL DGXVECTOR4::operator !=(const DGXVECTOR4& v) const	{	return IsNotEqual(x, v.x) || IsNotEqual(y, v.y) || IsNotEqual(z, v.z) || IsNotEqual(w,v.w);	}

// Dot Product
FLOAT DGXVECTOR4::operator *(const DGXVECTOR4& v)			{	return x    * v.x  + y    * v.y  + z    * v.z  + w * v.w;	  }
FLOAT operator *(const DGXVECTOR4& v1, const DGXVECTOR4& v2){	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }


// Transform: vector * Matrix4x4
DGXVECTOR4 DGXVECTOR4::operator *(const FLOAT* v)
{
	FLOAT X = x * v[0] + y * v[4] + z * v[ 8] + w * v[12];
	FLOAT Y = x * v[1] + y * v[5] + z * v[ 9] + w * v[13];
	FLOAT Z = x * v[2] + y * v[6] + z * v[10] + w * v[14];
	FLOAT W = x * v[3] + y * v[7] + z * v[11] + w * v[15];

	return DGXVECTOR4(X, Y, Z, W);
}

// Transform: Matrix4x4 * vector;
DGXVECTOR4 operator *(const FLOAT* v1, const DGXVECTOR4& v2)
{
	FLOAT X = v2.x * v1[ 0] + v2.y * v1[ 1] + v2.z * v1[ 2] +  v2.w * v1[ 3];
	FLOAT Y = v2.x * v1[ 4] + v2.y * v1[ 5] + v2.z * v1[ 6] +  v2.w * v1[ 7];
	FLOAT Z = v2.x * v1[ 8] + v2.y * v1[ 9] + v2.z * v1[10] +  v2.w * v1[11];
	FLOAT W = v2.x * v1[12] + v2.y * v1[13] + v2.z * v1[14] +  v2.w * v1[15];

	return DGXVECTOR4(X, Y, Z, W);
}


FLOAT DGXVECTOR4::Length()	{	return (FLOAT)sqrt(x*x + y*y + z*z + w*w);		}
FLOAT DGXVECTOR4::LengthSq(){	return(x*x + y*y + z*z + w*w);					}

DGXVECTOR4 DGXVECTOR4::Normalize()
{
	FLOAT l = this->Length();
	if(0.0F == l)
		return *this;

	l = 1.0F/l;
	x *= l;	y *= l;	z *= l;	w *= l;
	return *this;
}


DGXVECTOR4 DGXVECTOR4::Normalize(const DGXVECTOR4* v)
{
	*this = v;
	FLOAT l = this->Length();
	if(l == 0)
		return *this;

	l = 1.0F/l;
	x *= l;	y *= l;	z *= l;	w *= l;

	return *this;
}



////////////////////////////////////////////////////////////////////////////////
// Matrix

DGXMATRIX::DGXMATRIX()
{
	_11 = 1.0F;  _12 = 0.0F;  _13 = 0.0F;  _14 = 0.0F;
	_21 = 0.0F;  _22 = 1.0F;  _23 = 0.0F;  _24 = 0.0F;
	_31 = 0.0F;  _32 = 0.0F;  _33 = 1.0F;  _34 = 0.0F;
	_41 = 0.0F;  _42 = 0.0F;  _43 = 0.0F;  _44 = 1.0F;
}

DGXMATRIX::DGXMATRIX(const DGXMATRIX& v)
{
	_11 = v._11; _12 = v._12; _13 = v._13; _14 = v._14;
	_21 = v._21; _22 = v._22; _23 = v._23; _24 = v._24;
	_31 = v._31; _32 = v._32; _33 = v._33; _34 = v._34;
	_41 = v._41; _42 = v._42; _43 = v._43; _44 = v._44;
}

DGXMATRIX::DGXMATRIX(const FLOAT* v)
{
	if(!v)
		return;

	_11 = v[ 0]; _12 = v[ 1]; _13 = v[ 2]; _14 = v[ 3];
	_21 = v[ 4]; _22 = v[ 5]; _23 = v[ 6]; _24 = v[ 7];
	_31 = v[ 8]; _32 = v[ 9]; _33 = v[10]; _34 = v[11];
	_41 = v[12]; _42 = v[13]; _43 = v[14]; _44 = v[15];
}

DGXMATRIX::DGXMATRIX(const DGXMATRIX* v)
{
	if(!v)
		return;

	_11 = v->_11; _12 = v->_11; _13 = v->_11; _14 = v->_11;
	_21 = v->_21; _22 = v->_21; _23 = v->_21; _24 = v->_21;
	_31 = v->_31; _32 = v->_31; _33 = v->_31; _34 = v->_31;
	_41 = v->_41; _42 = v->_41; _43 = v->_41; _44 = v->_41;
}


DGXMATRIX::DGXMATRIX(FLOAT v11, FLOAT v12, FLOAT v13, FLOAT v14,
					 FLOAT v21, FLOAT v22, FLOAT v23, FLOAT v24,
					 FLOAT v31, FLOAT v32, FLOAT v33, FLOAT v34,
					 FLOAT v41, FLOAT v42, FLOAT v43, FLOAT v44 )
{
	_11 = v11; _12 = v12; _13 = v13; _14 = v14;
	_21 = v21; _22 = v22; _23 = v23; _24 = v24;
	_31 = v31; _32 = v32; _33 = v33; _34 = v34;
	_41 = v41; _42 = v42; _43 = v43; _44 = v44;
}


DGXMATRIX::DGXMATRIX(const DGE_MATRIX& v)
{
	_11 = v._11; _12 = v._12; _13 = v._13; _14 = v._14;
	_21 = v._21; _22 = v._22; _23 = v._23; _24 = v._24;
	_31 = v._31; _32 = v._32; _33 = v._33; _34 = v._34;
	_41 = v._41; _42 = v._42; _43 = v._43; _44 = v._44;
}



// access grants
FLOAT& DGXMATRIX::operator()(INT iRow, INT iCol )	{	return m[iRow][iCol];	}
FLOAT DGXMATRIX::operator()(INT iRow, INT iCol ) const{	return m[iRow][iCol];	}

// casting operators
DGXMATRIX::operator FLOAT*()				{	return(FLOAT*)&_11;		}
DGXMATRIX::operator const FLOAT*() const	{	return(FLOAT*)&_11;		}

// assignment operators
DGXMATRIX& DGXMATRIX::operator *=(const DGXMATRIX& v)
{
	DGXMATRIX t = *this;
	_11 = t._11 * v._11 +  t._12 * v._21 +  t._13 * v._31 +  t._14 * v._41;
	_12 = t._11 * v._12 +  t._12 * v._22 +  t._13 * v._32 +  t._14 * v._42;
	_13 = t._11 * v._13 +  t._12 * v._23 +  t._13 * v._33 +  t._14 * v._43;
	_14 = t._11 * v._14 +  t._12 * v._24 +  t._13 * v._34 +  t._14 * v._44;

	_21 = t._21 * v._11 +  t._22 * v._21 +  t._23 * v._31 +  t._24 * v._41;
	_22 = t._21 * v._12 +  t._22 * v._22 +  t._23 * v._32 +  t._24 * v._42;
	_23 = t._21 * v._13 +  t._22 * v._23 +  t._23 * v._33 +  t._24 * v._43;
	_24 = t._21 * v._14 +  t._22 * v._24 +  t._23 * v._34 +  t._24 * v._44;

	_31 = t._31 * v._11 +  t._32 * v._21 +  t._33 * v._31 +  t._34 * v._41;
	_32 = t._31 * v._12 +  t._32 * v._22 +  t._33 * v._32 +  t._34 * v._42;
	_33 = t._31 * v._13 +  t._32 * v._23 +  t._33 * v._33 +  t._34 * v._43;
	_34 = t._31 * v._14 +  t._32 * v._24 +  t._33 * v._34 +  t._34 * v._44;

	_41 = t._41 * v._11 +  t._42 * v._21 +  t._43 * v._31 +  t._44 * v._41;
	_42 = t._41 * v._12 +  t._42 * v._22 +  t._43 * v._32 +  t._44 * v._42;
	_43 = t._41 * v._13 +  t._42 * v._23 +  t._43 * v._33 +  t._44 * v._43;
	_44 = t._41 * v._14 +  t._42 * v._24 +  t._43 * v._34 +  t._44 * v._44;

	return * this;
}


DGXMATRIX& DGXMATRIX::operator +=(const DGXMATRIX& v)
{
	_11 += v._11;	_12 += v._12;	_13 += v._13;	_14 += v._14;
	_21 += v._21;	_22 += v._22;	_23 += v._23;	_24 += v._24;
	_31 += v._31;	_32 += v._32;	_33 += v._33;	_34 += v._34;
	_41 += v._41;	_42 += v._42;	_43 += v._43;	_44 += v._44;

	return * this;
}

DGXMATRIX& DGXMATRIX::operator -=(const DGXMATRIX& v)
{
	_11 -= v._11;	_12 -= v._12;	_13 -= v._13;	_14 -= v._14;
	_21 -= v._21;	_22 -= v._22;	_23 -= v._23;	_24 -= v._24;
	_31 -= v._31;	_32 -= v._32;	_33 -= v._33;	_34 -= v._34;
	_41 -= v._41;	_42 -= v._42;	_43 -= v._43;	_44 -= v._44;

	return * this;
}

DGXMATRIX& DGXMATRIX::operator *=(FLOAT v)
{
	_11 *= v;	_12 *= v;	_13 *= v;	_14 *= v;
	_21 *= v;	_22 *= v;	_23 *= v;	_24 *= v;
	_31 *= v;	_32 *= v;	_33 *= v;	_34 *= v;
	_41 *= v;	_42 *= v;	_43 *= v;	_44 *= v;

	return * this;
}

DGXMATRIX& DGXMATRIX::operator /=(FLOAT v)
{
	v = 1.0F/v;
	_11 *= v;	_12 *= v;	_13 *= v;	_14 *= v;
	_21 *= v;	_22 *= v;	_23 *= v;	_24 *= v;
	_31 *= v;	_32 *= v;	_33 *= v;	_34 *= v;
	_41 *= v;	_42 *= v;	_43 *= v;	_44 *= v;

	return * this;
}


// unary operators
DGXMATRIX DGXMATRIX::operator +() const
{
	return *this;
}

DGXMATRIX DGXMATRIX::operator -() const
{
	return DGXMATRIX(	-_11, -_12, -_13, -_14,
		-_21, -_22, -_23, -_24,
		-_31, -_32, -_33, -_34,
		-_41, -_42, -_43, -_44);
}

// binary operators
DGXMATRIX DGXMATRIX::operator *(const DGXMATRIX& v) const
{
	DGXMATRIX t = *this;
	DGXMATRIX r;
	r._11 = t._11 * v._11 +  t._12 * v._21 +  t._13 * v._31 +  t._14 * v._41;
	r._12 = t._11 * v._12 +  t._12 * v._22 +  t._13 * v._32 +  t._14 * v._42;
	r._13 = t._11 * v._13 +  t._12 * v._23 +  t._13 * v._33 +  t._14 * v._43;
	r._14 = t._11 * v._14 +  t._12 * v._24 +  t._13 * v._34 +  t._14 * v._44;

	r._21 = t._21 * v._11 +  t._22 * v._21 +  t._23 * v._31 +  t._24 * v._41;
	r._22 = t._21 * v._12 +  t._22 * v._22 +  t._23 * v._32 +  t._24 * v._42;
	r._23 = t._21 * v._13 +  t._22 * v._23 +  t._23 * v._33 +  t._24 * v._43;
	r._24 = t._21 * v._14 +  t._22 * v._24 +  t._23 * v._34 +  t._24 * v._44;

	r._31 = t._31 * v._11 +  t._32 * v._21 +  t._33 * v._31 +  t._34 * v._41;
	r._32 = t._31 * v._12 +  t._32 * v._22 +  t._33 * v._32 +  t._34 * v._42;
	r._33 = t._31 * v._13 +  t._32 * v._23 +  t._33 * v._33 +  t._34 * v._43;
	r._34 = t._31 * v._14 +  t._32 * v._24 +  t._33 * v._34 +  t._34 * v._44;

	r._41 = t._41 * v._11 +  t._42 * v._21 +  t._43 * v._31 +  t._44 * v._41;
	r._42 = t._41 * v._12 +  t._42 * v._22 +  t._43 * v._32 +  t._44 * v._42;
	r._43 = t._41 * v._13 +  t._42 * v._23 +  t._43 * v._33 +  t._44 * v._43;
	r._44 = t._41 * v._14 +  t._42 * v._24 +  t._43 * v._34 +  t._44 * v._44;

	return r;
}


DGXMATRIX DGXMATRIX::operator +(const DGXMATRIX& v) const
{
	return DGXMATRIX(
		_11 + v._11, _12 + v._12, _13 + v._13, _14 + v._14,
		_21 + v._21, _22 + v._22, _23 + v._23, _24 + v._24,
		_31 + v._31, _32 + v._32, _33 + v._33, _34 + v._34,
		_41 + v._41, _42 + v._42, _43 + v._43, _44 + v._44
		);
}

DGXMATRIX DGXMATRIX::operator -(const DGXMATRIX& v) const
{
	return DGXMATRIX(
		_11 - v._11, _12 - v._12, _13 - v._13, _14 - v._14,
		_21 - v._21, _22 - v._22, _23 - v._23, _24 - v._24,
		_31 - v._31, _32 - v._32, _33 - v._33, _34 - v._34,
		_41 - v._41, _42 - v._42, _43 - v._43, _44 - v._44
		);
}

DGXMATRIX DGXMATRIX::operator *(FLOAT v) const
{
	return DGXMATRIX(
		_11 * v, _12 * v, _13 * v, _14 * v,
		_21 * v, _22 * v, _23 * v, _24 * v,
		_31 * v, _32 * v, _33 * v, _34 * v,
		_41 * v, _42 * v, _43 * v, _44 * v
		);
}

DGXMATRIX DGXMATRIX::operator /(FLOAT v) const
{
	v = 1.0F / v;
	return DGXMATRIX(
		_11 * v, _12 * v, _13 * v, _14 * v,
		_21 * v, _22 * v, _23 * v, _24 * v,
		_31 * v, _32 * v, _33 * v, _34 * v,
		_41 * v, _42 * v, _43 * v, _44 * v
		);
}


DGXMATRIX operator *(FLOAT f, const DGXMATRIX& v)
{
	return DGXMATRIX(
		f * v._11, f * v._12, f * v._13, f * v._14,
		f * v._21, f * v._22, f * v._23, f * v._24,
		f * v._31, f * v._32, f * v._33, f * v._34,
		f * v._41, f * v._42, f * v._43, f * v._44
		);
}

DGXMATRIX operator *(const DGXMATRIX& v, FLOAT f)
{
	return DGXMATRIX(
		f * v._11, f * v._12, f * v._13, f * v._14,
		f * v._21, f * v._22, f * v._23, f * v._24,
		f * v._31, f * v._32, f * v._33, f * v._34,
		f * v._41, f * v._42, f * v._43, f * v._44
		);
}


//BOOL DGXMATRIX::operator ==(const DGXMATRIX& v) const
//{
//	return	(
//		_11 == v._11 && _12 == v._12 && _13 == v._13 && _14 == v._14 &&
//		_21 == v._21 && _22 == v._22 && _23 == v._23 && _24 == v._24 &&
//		_31 == v._31 && _32 == v._32 && _33 == v._33 && _34 == v._34 &&
//		_41 == v._41 && _42 == v._42 && _43 == v._43 && _44 == v._44
//		);
//}
//
//BOOL DGXMATRIX::operator !=(const DGXMATRIX& v) const
//{
//	return	(
//		_11 != v._11 || _12 != v._12 || _13 != v._13 || _14 != v._14 ||
//		_21 != v._21 || _22 != v._22 || _23 != v._23 || _24 != v._24 ||
//		_31 != v._31 || _32 != v._32 || _33 != v._33 || _34 != v._34 ||
//		_41 != v._41 || _42 != v._42 || _43 != v._43 || _44 != v._44
//		);
//}

BOOL DGXMATRIX::operator ==(const DGXMATRIX& v) const
{
	return	(
		 IsEqual(_11,v._11) && IsEqual(_12, v._12) && IsEqual(_13, v._13) && IsEqual(_14, v._14) &&
		 IsEqual(_21,v._21) && IsEqual(_22, v._22) && IsEqual(_23, v._23) && IsEqual(_24, v._24) &&
		 IsEqual(_31,v._31) && IsEqual(_32, v._32) && IsEqual(_33, v._33) && IsEqual(_34, v._34) &&
		 IsEqual(_41,v._41) && IsEqual(_42, v._42) && IsEqual(_43, v._43) && IsEqual(_44, v._44)
		);
}

BOOL DGXMATRIX::operator !=(const DGXMATRIX& v) const
{
	return	(
		IsNotEqual(_11, v._11) || IsNotEqual(_12, v._12) || IsNotEqual(_13, v._13) || IsNotEqual(_14, v._14) ||
		IsNotEqual(_21, v._21) || IsNotEqual(_22, v._22) || IsNotEqual(_23, v._23) || IsNotEqual(_24, v._24) ||
		IsNotEqual(_31, v._31) || IsNotEqual(_32, v._32) || IsNotEqual(_33, v._33) || IsNotEqual(_34, v._34) ||
		IsNotEqual(_41, v._41) || IsNotEqual(_42, v._42) || IsNotEqual(_43, v._43) || IsNotEqual(_44, v._44)
		);
}



// Length
DGXMATRIX& DGXMATRIX::Identity()
{
	_11=1.0F; _12=0.0F; _13=0.0F; _14=0.0F;
	_21=0.0F; _22=1.0F; _23=0.0F; _24=0.0F;
	_31=0.0F; _32=0.0F; _33=1.0F; _34=0.0F;
	_41=0.0F; _42=0.0F; _43=0.0F; _44=1.0F;
	return *this;
}


DGXMATRIX& DGXMATRIX::Transpose()
{
	FLOAT t =0.0F;

	t   = _12;	_12 = _21;	_21 = t;
	t   = _13;	_13 = _31;	_31 = t;
	t   = _14;	_14 = _41;	_41 = t;

	t   = _23;	_23 = _32;	_32 = t;
	t   = _24;	_24 = _42;	_42 = t;

	t   = _34;	_34 = _43;	_43 = t;

	return *this;
}


DGXMATRIX& DGXMATRIX::Transpose(const DGXMATRIX* v)
{
	FLOAT t =0.0F;
	*this = *v;

	t   = _12;	_12 = _21;	_21 = t;
	t   = _13;	_13 = _31;	_31 = t;
	t   = _14;	_14 = _41;	_41 = t;

	t   = _23;	_23 = _32;	_32 = t;
	t   = _24;	_24 = _42;	_42 = t;

	t   = _34;	_34 = _43;	_43 = t;

	return *this;
}


DGXMATRIX& DGXMATRIX::Inverse(INT nQuick)
{
	DGXMATRIX	t = *this;
	this->Inverse(&t, nQuick);
	return *this;
}


DGXMATRIX& DGXMATRIX::Inverse(const DGXMATRIX* pIn, INT nQuick)
{
	if(TRUE == nQuick)
	{
		FLOAT fDet = 1.0F;

		// 4X4 행렬은 Determinant를 1로 정한다.
		fDet =
			pIn->_11 * ( pIn->_22 * pIn->_33 - pIn->_23 * pIn->_32 ) +
			pIn->_12 * ( pIn->_23 * pIn->_31 - pIn->_21 * pIn->_33 ) +
			pIn->_13 * ( pIn->_21 * pIn->_32 - pIn->_22 * pIn->_31 );

		fDet = 1.0F / fDet;

		this->_11 =  fDet * ( pIn->_22 * pIn->_33 - pIn->_23 * pIn->_32 );
		this->_12 = -fDet * ( pIn->_12 * pIn->_33 - pIn->_13 * pIn->_32 );
		this->_13 =  fDet * ( pIn->_12 * pIn->_23 - pIn->_13 * pIn->_22 );
		this->_14 = 0.0F;

		this->_21 = -fDet * ( pIn->_21 * pIn->_33 - pIn->_23 * pIn->_31 );
		this->_22 =  fDet * ( pIn->_11 * pIn->_33 - pIn->_13 * pIn->_31 );
		this->_23 = -fDet * ( pIn->_11 * pIn->_23 - pIn->_13 * pIn->_21 );
		this->_24 = 0.0F;

		this->_31 =  fDet * ( pIn->_21 * pIn->_32 - pIn->_22 * pIn->_31 );
		this->_32 = -fDet * ( pIn->_11 * pIn->_32 - pIn->_12 * pIn->_31 );
		this->_33 =  fDet * ( pIn->_11 * pIn->_22 - pIn->_12 * pIn->_21 );
		this->_34 = 0.0F;

		this->_41 = -( pIn->_41 * this->_11 + pIn->_42 * this->_21 + pIn->_43 * this->_31 );
		this->_42 = -( pIn->_41 * this->_12 + pIn->_42 * this->_22 + pIn->_43 * this->_32 );
		this->_43 = -( pIn->_41 * this->_13 + pIn->_42 * this->_23 + pIn->_43 * this->_33 );
		this->_44 = 1.0F;

		return *this;
	}

	// this code came from Intel.

	float*	v = (float*)pIn;
	float*	p = &m[0][0];

	float tmp[12]; /* temp array for pairs */
	float src[16]; /* array of transpose source matrix */
	float det; /* determinant */
	/* transpose matrix */
	for (int i = 0; i < 4; i++)
	{
		src[i     ] = v[i*4    ];
		src[i + 4 ] = v[i*4 + 1];
		src[i + 8 ] = v[i*4 + 2];
		src[i + 12] = v[i*4 + 3];
	}
	/* calculate pairs for first 8 elements (cofactors) */
	tmp[ 0] = src[10] * src[15];
	tmp[ 1] = src[11] * src[14];
	tmp[ 2] = src[ 9] * src[15];
	tmp[ 3] = src[11] * src[13];
	tmp[ 4] = src[ 9] * src[14];
	tmp[ 5] = src[10] * src[13];
	tmp[ 6] = src[ 8] * src[15];
	tmp[ 7] = src[11] * src[12];
	tmp[ 8] = src[ 8] * src[14];
	tmp[ 9] = src[10] * src[12];
	tmp[10] = src[ 8] * src[13];
	tmp[11] = src[ 9] * src[12];
	/* calculate first 8 elements (cofactors) */
	p[0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[ 4]*src[7];
	p[0]-= tmp[1]*src[5] + tmp[2]*src[6] + tmp[ 5]*src[7];
	p[1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[ 9]*src[7];
	p[1]-= tmp[0]*src[4] + tmp[7]*src[6] + tmp[ 8]*src[7];
	p[2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
	p[2]-= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
	p[3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
	p[3]-= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
	p[4] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[ 5]*src[3];
	p[4]-= tmp[0]*src[1] + tmp[3]*src[2] + tmp[ 4]*src[3];
	p[5] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[ 8]*src[3];
	p[5]-= tmp[1]*src[0] + tmp[6]*src[2] + tmp[ 9]*src[3];
	p[6] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
	p[6]-= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
	p[7] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
	p[7]-= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];


	/* calculate pairs for second 8 elements (cofactors) */
	tmp[ 0] = src[2]*src[7];
	tmp[ 1] = src[3]*src[6];
	tmp[ 2] = src[1]*src[7];
	tmp[ 3] = src[3]*src[5];
	tmp[ 4] = src[1]*src[6];
	tmp[ 5] = src[2]*src[5];
	tmp[ 6] = src[0]*src[7];
	tmp[ 7] = src[3]*src[4];
	tmp[ 8] = src[0]*src[6];
	tmp[ 9] = src[2]*src[4];
	tmp[10] = src[0]*src[5];
	tmp[11] = src[1]*src[4];
	/* calculate second 8 elements (cofactors) */
	p[ 8] = tmp[ 0]*src[13] + tmp[ 3]*src[14] + tmp[ 4]*src[15];
	p[ 8]-= tmp[ 1]*src[13] + tmp[ 2]*src[14] + tmp[ 5]*src[15];
	p[ 9] = tmp[ 1]*src[12] + tmp[ 6]*src[14] + tmp[ 9]*src[15];
	p[ 9]-= tmp[ 0]*src[12] + tmp[ 7]*src[14] + tmp[ 8]*src[15];
	p[10] = tmp[ 2]*src[12] + tmp[ 7]*src[13] + tmp[10]*src[15];
	p[10]-= tmp[ 3]*src[12] + tmp[ 6]*src[13] + tmp[11]*src[15];
	p[11] = tmp[ 5]*src[12] + tmp[ 8]*src[13] + tmp[11]*src[14];
	p[11]-= tmp[ 4]*src[12] + tmp[ 9]*src[13] + tmp[10]*src[14];
	p[12] = tmp[ 2]*src[10] + tmp[ 5]*src[11] + tmp[ 1]*src[ 9];
	p[12]-= tmp[ 4]*src[11] + tmp[ 0]*src[ 9] + tmp[ 3]*src[10];
	p[13] = tmp[ 8]*src[11] + tmp[ 0]*src[ 8] + tmp[ 7]*src[10];
	p[13]-= tmp[ 6]*src[10] + tmp[ 9]*src[11] + tmp[ 1]*src[ 8];
	p[14] = tmp[ 6]*src[ 9] + tmp[11]*src[11] + tmp[ 3]*src[ 8];
	p[14]-= tmp[10]*src[11] + tmp[ 2]*src[ 8] + tmp[ 7]*src[ 9];
	p[15] = tmp[10]*src[10] + tmp[ 4]*src[ 8] + tmp[ 9]*src[ 9];
	p[15]-= tmp[ 8]*src[ 9] + tmp[11]*src[10] + tmp[ 5]*src[ 8];
	/* calculate determinant */
	det=src[0]*p[0]+src[1]*p[1]+src[2]*p[2]+src[3]*p[3];
	/* calculate matrix inverse */
	det = 1.0F/det;
	for (int j = 0; j < 16; j++)
		p[j] *= det;


	return *this;
}


FLOAT DGXMATRIX::Determinant()
{
	FLOAT t =0;

	t += (_24 * _11 - _14 * _21) * (_32 * _43 - _33 * _42);
	t += (_24 * _12 - _14 * _22) * (_33 * _41 - _31 * _43);
	t += (_24 * _13 - _14 * _23) * (_31 * _42 - _32 * _41);

	t += (_44 * _31 - _34 * _41) * (_12 * _23 - _13 * _22);
	t += (_44 * _32 - _34 * _42) * (_13 * _21 - _11 * _23);
	t += (_44 * _33 - _34 * _43) * (_11 * _22 - _12 * _21);

	return t;
}


DGXMATRIX& DGXMATRIX::SetupScaling(FLOAT X, FLOAT Y, FLOAT Z)
{
	this->Identity();
	_11 = X;    _22 = Y;    _33 = Z;
	return *this;
}




DGXMATRIX& DGXMATRIX::SetupViewLH(const DGXVECTOR3* pEye, const DGXVECTOR3* pLook, const DGXVECTOR3* pUp)
{
	DGXVECTOR3 vcX;
	DGXVECTOR3 vcY;
	DGXVECTOR3 vcZ;

	vcZ = *pLook - *pEye;
	vcZ.Normalize();

	vcX	= *pUp ^ vcZ;
	vcX.Normalize();

	vcY = vcZ ^ vcX;

	this->Identity();

	_11 = vcX.x;    _12 = vcY.x;    _13 = vcZ.x;
	_21 = vcX.y;    _22 = vcY.y;    _23 = vcZ.y;
	_31 = vcX.z;    _32 = vcY.z;    _33 = vcZ.z;

	_41 = - *pEye * vcX;
	_42 = - *pEye * vcY;
	_43 = - *pEye * vcZ;

	return *this;
}


DGXMATRIX& DGXMATRIX::SetupViewRH(const DGXVECTOR3* pEye, const DGXVECTOR3* pLook, const DGXVECTOR3* pUp)
{
//	DGXVECTOR3 vcX;
//	DGXVECTOR3 vcY;
//	DGXVECTOR3 vcZ;
//
//	vcZ = *pLook - *pEye;
//	vcZ.Normalize();
//
//	vcX	= *pUp ^ vcZ;
//	vcX.Normalize();
//
//	vcY = vcZ ^ vcX;
//

	DGXVECTOR3 vcX;
	DGXVECTOR3 vcY;
	DGXVECTOR3 vcZ;

	vcY = *pLook - *pEye;
	vcY.Normalize();

	vcX	= vcY^ *pUp;
	vcX.Normalize();

	vcZ = vcX ^ vcY;





	this->Identity();

	_11 = vcX.x;    _12 = vcY.x;    _13 = vcZ.x;
	_21 = vcX.y;    _22 = vcY.y;    _23 = vcZ.y;
	_31 = vcX.z;    _32 = vcY.z;    _33 = vcZ.z;

	_41 = - *pEye * vcX;
	_42 = - *pEye * vcY;
	_43 = - *pEye * vcZ;

	return *this;
}


DGXMATRIX& DGXMATRIX::SetupPerspectiveLH(FLOAT fFov, FLOAT fAsp, FLOAT fNear, FLOAT fFar)
{
	fFov	*=0.5f;
	FLOAT cot = (FLOAT)cos(fFov)/(FLOAT)sin(fFov);

	FLOAT h = cot;
	FLOAT w = cot/fAsp;

	this->Identity();

	_11 = w;
	_22 = h;
	_33 =            fFar / ( fFar - fNear );
	_34 = 1.0F;
	_43 = (-fNear * fFar) / ( fFar - fNear );
	_44 = 0.0F;

	return *this;
}


DGXMATRIX& DGXMATRIX::SetupPerspectiveRH(FLOAT fFov, FLOAT fAsp, FLOAT fNear, FLOAT fFar)
{
	fFov	*=0.5f;
	FLOAT cot = (FLOAT)cos(fFov)/(FLOAT)sin(fFov);

	FLOAT h = cot;
	FLOAT w = cot/fAsp;

	this->Identity();

	_11 = w;
	_22 = h;
	_33 = (     fNear + fFar) / (fNear - fFar);
	_34 = -1.f;
	_43 = ( 2 * fNear * fFar) / (fNear - fFar);
	_44 = 0.f;

	return *this;
}


DGXMATRIX& DGXMATRIX::SetupRotationX(FLOAT fRad)
{
	this->Identity();
	_22 =  (FLOAT)cos( fRad );
	_23 =  (FLOAT)sin( fRad );
	_32 = -(FLOAT)sin( fRad );
	_33 =  (FLOAT)cos( fRad );
	return *this;
}


DGXMATRIX& DGXMATRIX::SetupRotationY(FLOAT fRads)
{
	this->Identity();
	_11 =  (FLOAT)cos( fRads );
	_13 = -(FLOAT)sin( fRads );
	_31 =  (FLOAT)sin( fRads );
	_33 =  (FLOAT)cos( fRads );
	return *this;
}


DGXMATRIX& DGXMATRIX::SetupRotationZ(FLOAT fRads)
{
	this->Identity();
	_11  =  (FLOAT)cos( fRads );
	_12  =  (FLOAT)sin( fRads );
	_21  = -(FLOAT)sin( fRads );
	_22  =  (FLOAT)cos( fRads );
	return *this;
}


DGXMATRIX& DGXMATRIX::SetupRotationAxis(const DGXVECTOR3* vAxis, FLOAT fRad)
{
	FLOAT     fCos = (FLOAT)cos( fRad );
	FLOAT     fSin = (FLOAT)sin( fRad );
	DGXVECTOR3 v    = *vAxis;

	v.Normalize();

	this->Identity();

	_11 = ( v.x * v.x ) * ( 1.0F - fCos ) + fCos;
	_12 = ( v.x * v.y ) * ( 1.0F - fCos ) - (v.z * fSin);
	_13 = ( v.x * v.z ) * ( 1.0F - fCos ) + (v.y * fSin);

	_21 = ( v.y * v.x ) * ( 1.0F - fCos ) + (v.z * fSin);
	_22 = ( v.y * v.y ) * ( 1.0F - fCos ) + fCos ;
	_23 = ( v.y * v.z ) * ( 1.0F - fCos ) - (v.x * fSin);

	_31 = ( v.z * v.x ) * ( 1.0F - fCos ) - (v.y * fSin);
	_32 = ( v.z * v.y ) * ( 1.0F - fCos ) + (v.x * fSin);
	_33 = ( v.z * v.z ) * ( 1.0F - fCos ) + fCos;

	return *this;
}


DGXMATRIX& DGXMATRIX::SetupTranslation(const DGXVECTOR3* vTrs, BOOL bInit)
{
	if(bInit)
		this->Identity();

	_41 = vTrs->x;
	_42 = vTrs->y;
	_43 = vTrs->z;

	return *this;
}


void DGXMATRIX::TransformCoord(DGXVECTOR3* pOut, const DGXVECTOR3* pIn)
{
	FLOAT	_x, _y, _z;
	FLOAT	x, y, z, w;

	_x = pIn->x;
	_y = pIn->y;
	_z = pIn->z;

	x = _11 * _x +  _21 * _y + _31 * _z   +  _41;
	y = _12 * _x +  _22 * _y + _32 * _z   +  _42;
	z = _13 * _x +  _23 * _y + _33 * _z   +  _43;
	w = _14 * _x +  _24 * _y + _34 * _z   +  _44;

	x /=w;
	y /=w;
	z /=w;
	w =1.0F;

	pOut->x =x;
	pOut->y =y;
	pOut->z =z;

}



////////////////////////////////////////////////////////////////////////////////
// Quaternion

DGXQUATERNION::DGXQUATERNION()						{	x=0.0F; y=0.0F; z=0.0F; w=1.0F;		}
DGXQUATERNION::DGXQUATERNION(const DGXQUATERNION& v){	x=v.x; y=v.y; z=v.z; w=v.w;			}
DGXQUATERNION::DGXQUATERNION(const FLOAT* v)		{	if(!v) return; x=v[0]; y=v[1]; z=v[2]; w=v[3];	}
DGXQUATERNION::DGXQUATERNION(const DGXQUATERNION* v){	if(!v) return; x=v->x; y=v->y; z=v->z; w=v->w;	}
DGXQUATERNION::DGXQUATERNION(FLOAT X,FLOAT Y,FLOAT Z,FLOAT W){	x=X; y=Y; z=Z; w=W;	}
DGXQUATERNION::DGXQUATERNION(const DGE_FLOAT4& v)	{	x=v.x; y=v.y; z=v.z; w=v.w;			}


// casting
DGXQUATERNION::operator FLOAT* ()				{	return (FLOAT *) &x;		}
DGXQUATERNION::operator const FLOAT* () const	{	return (const FLOAT *) &x;	}
FLOAT& DGXQUATERNION::operator[](INT n)			{	return *((&x)+ n);			}

// assignment operators
DGXQUATERNION& DGXQUATERNION::operator += (const DGXQUATERNION& q ){ x +=q.x; y +=q.y; z +=q.z; w +=q.w; return *this;	}
DGXQUATERNION& DGXQUATERNION::operator -= (const DGXQUATERNION& q ){ x -=q.x; y -=q.y; z -=q.z; w -=q.w; return *this;	}
DGXQUATERNION& DGXQUATERNION::operator *= (const DGXQUATERNION& q )
{
	DGXQUATERNION q1 = *this;
	DGXQUATERNION q2 = q;

	this->w = q1.w * q2.w - ( q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);

	this->x = q1.w * q2.x + q2.w * q1.x + (q1.y * q2.z - q1.z * q2.y);
	this->y = q1.w * q2.y + q2.w * q1.y + (q1.z * q2.x - q1.x * q2.z);
	this->z = q1.w * q2.z + q2.w * q1.z + (q1.x * q2.y - q1.y * q2.x);

	return *this;
}

DGXQUATERNION& DGXQUATERNION::operator *= ( FLOAT f){					x *=f; y *=f; z *=f; w *=f; return *this;	}
DGXQUATERNION& DGXQUATERNION::operator /= ( FLOAT f){	FLOAT t=1.0F/f;	x *=t; y *=t; z *=t; w *=t; return *this;	}

// unary operators
DGXQUATERNION DGXQUATERNION::operator +() const	{	return *this;							}
DGXQUATERNION DGXQUATERNION::operator -() const	{	return DGXQUATERNION(-x, -y, -z, -w);	}

// binary operators
DGXQUATERNION DGXQUATERNION::operator +(const DGXQUATERNION& v) const {	return DGXQUATERNION(x + v.x, y + v.y, z + v.z, w + v.w);	}
DGXQUATERNION DGXQUATERNION::operator -(const DGXQUATERNION& v) const {	return DGXQUATERNION(x - v.x, y - v.y, z - v.z, w - v.w);	}
DGXQUATERNION DGXQUATERNION::operator *(const DGXQUATERNION& q) const
{
	DGXQUATERNION q1 = *this;
	DGXQUATERNION q2 = q;

	DGXQUATERNION qT;

	qT.w = q1.w * q2.w - ( q1.x * q2.x + q1.y * q2.y + q1.z * q2.z);

	qT.x = q1.w * q2.x + q2.w * q1.x + (q1.y * q2.z - q1.z * q2.y);
	qT.y = q1.w * q2.y + q2.w * q1.y + (q1.z * q2.x - q1.x * q2.z);
	qT.z = q1.w * q2.z + q2.w * q1.z + (q1.x * q2.y - q1.y * q2.x);

	return qT;
}

DGXQUATERNION DGXQUATERNION::operator *(FLOAT v) const	{	return DGXQUATERNION(x * v  , y * v  , z * v  , w * v  );	}
DGXQUATERNION operator *(FLOAT f, const DGXQUATERNION& v){	return DGXQUATERNION(f * v.x, f * v.y, f * v.z, f * v.w);	}


//BOOL DGXQUATERNION::operator == (const DGXQUATERNION& v) const {	return x == v.x && y == v.y && z == v.z && w == v.w;	}
//BOOL DGXQUATERNION::operator != (const DGXQUATERNION& v) const {	return x != v.x || y != v.y || z != v.z || w != v.w;	}

BOOL DGXQUATERNION::operator ==(const DGXQUATERNION& v) const {	return IsEqual(x, v.x)    && IsEqual(y, v.y)    && IsEqual(z, v.z)    && IsEqual(w,v.w);	}
BOOL DGXQUATERNION::operator !=(const DGXQUATERNION& v) const {	return IsNotEqual(x, v.x) || IsNotEqual(y, v.y) || IsNotEqual(z, v.z) || IsNotEqual(w,v.w);	}




void DGXQUATERNION::SLerp(const DGXQUATERNION* q1, const DGXQUATERNION* q2, FLOAT t)
{
	DGXQUATERNION	q;

	//Q = (1/sinθ)[  sin (θ*(1-t)) * Q1 + sin (θ*t) * Q2]

	float w1;
	float w2;
	float dt = q1->x * q2->x + q1->y * q2->y + q1->z * q2->z + q1->w * q2->w;


	if( dt > 0.9999f || dt<-0.9999f)
	{
		w1 = 1.0F - t;
		w2 = t;
	}
	else
	{
		float fTheta  = (float)acos( fabsf(dt) );
		float fSin    = (float)sin( fTheta );

		w1 = (float)sin( (1.0F-t) * fTheta) / fSin;
		w2 = (float)sin(       t  * fTheta) / fSin;
	}

	if( dt < 0 )
		w2 = -w2;

	q = *q1 * w1 + *q2 * w2;

	*this = q;
}


void DGXQUATERNION::RotationMatrix(DGXMATRIX* pOut, BOOL bDX)
{
	float	xx = x * x;
	float	yy = y * y;
	float	zz = z * z;

	float	xy = x * y;
	float	yz = y * z;
	float	xz = z * x;

	float	xw = x * w;
	float	yw = y * w;
	float	zw = z * w;

	pOut->Identity();


	if(bDX)
	{
		// D3D
		pOut->_11 = 1 - 2*yy - 2*zz;	pOut->_21 =     2*xy - 2*zw;	pOut->_31 =     2*xz + 2*yw;
		pOut->_12 =     2*xy + 2*zw;	pOut->_22 = 1 - 2*xx - 2*zz;	pOut->_32 =     2*yz - 2*xw;
		pOut->_13 =     2*xz - 2*yw;	pOut->_23 =     2*yz + 2*xw;	pOut->_33 = 1 - 2*xx - 2*yy;
	}
	else
	{
		pOut->_11 = 1 - 2*yy - 2*zz;	pOut->_12 =     2*xy - 2*zw;	pOut->_13 =     2*xz + 2*yw;
		pOut->_21 =     2*xy + 2*zw;	pOut->_22 = 1 - 2*xx - 2*zz;	pOut->_23 =     2*yz - 2*xw;
		pOut->_31 =     2*xz - 2*yw;	pOut->_32 =     2*yz + 2*xw;	pOut->_33 = 1 - 2*xx - 2*yy;
	}
}




////////////////////////////////////////////////////////////////////////////////
// Color
DGXCOLOR::DGXCOLOR()							{	r=1.0F; g=1.0F; b=1.0F; a=1.0F;	}
DGXCOLOR::DGXCOLOR(const DGXCOLOR& v)			{	r=v.r ; g=v.g ; b=v.b ; a=v.a ; }
DGXCOLOR::DGXCOLOR(const FLOAT* v){	if(!v) return;	r=v[0];	g=v[1];	b=v[2];	a=v[3];	}
DGXCOLOR::DGXCOLOR(const DGXCOLOR* v){if(!v)return; r=v->r; g=v->g; b=v->b; a=v->a;	}
DGXCOLOR::DGXCOLOR(DWORD v)
{
	const FLOAT f = 1.0F / 255.F;
	r = f * (FLOAT) (unsigned char) (v >> 16);
	g = f * (FLOAT) (unsigned char) (v >>  8);
	b = f * (FLOAT) (unsigned char) (v >>  0);
	a = f * (FLOAT) (unsigned char) (v >> 24);
}

DGXCOLOR::DGXCOLOR(const BYTE* v/*r[0],g[1],b[2],a[3]*/)
{
	r = FLOAT(v[0])/255.F;
	g = FLOAT(v[1])/255.F;
	b = FLOAT(v[2])/255.F;
	a = FLOAT(v[3])/255.F;
}

DGXCOLOR::DGXCOLOR(FLOAT R,FLOAT G,FLOAT B,FLOAT A)	{	r=R; g=G; b=B; a=A; }
DGXCOLOR::DGXCOLOR(const DGE_COLORF& v)				{	r=v.r; g=v.g; b=v.b; a=v.a; }




// casting
DGXCOLOR::operator DWORD () const
{
	DWORD R = r >= 1.0F ? 0xff : r <= 0.0F ? 0x00 : (DWORD) (r * 255.F + 0.5f);
	DWORD G = g >= 1.0F ? 0xff : g <= 0.0F ? 0x00 : (DWORD) (g * 255.F + 0.5f);
	DWORD B = b >= 1.0F ? 0xff : b <= 0.0F ? 0x00 : (DWORD) (b * 255.F + 0.5f);
	DWORD A = a >= 1.0F ? 0xff : a <= 0.0F ? 0x00 : (DWORD) (a * 255.F + 0.5f);
	
	return (A << 24) | (R << 16) | (G << 8) | B;
}

DGXCOLOR::operator FLOAT *()			{	return (FLOAT*) &r;			}
DGXCOLOR::operator const FLOAT *() const{	return (const FLOAT*) &r;	}
FLOAT& DGXCOLOR::operator[](INT n)		{	return *((&r)+ n);			}

// assignment operators
DGXCOLOR& DGXCOLOR::operator +=(const DGXCOLOR& v){	r +=v.r; g +=v.g; b +=v.b; a +=v.a;	return *this;	}
DGXCOLOR& DGXCOLOR::operator -=(const DGXCOLOR& v){	r -=v.r; g -=v.g; b -=v.b; a -=v.a; return *this;	}
DGXCOLOR& DGXCOLOR::operator *=(FLOAT f)		{	r *=f;   g *=f;   b *=f;   a *= f;	return *this;	}
DGXCOLOR& DGXCOLOR::operator /=(FLOAT f){FLOAT t=1.0F/f; r *=t; g *=t; b *=t; a *=t;	return *this;	}

// unary operators
DGXCOLOR DGXCOLOR::operator +() const	{	return *this;						}
DGXCOLOR DGXCOLOR::operator -() const	{	return DGXCOLOR(-r, -g, -b, -a);	}

// binary operators
DGXCOLOR DGXCOLOR::operator +(const DGXCOLOR& v) const{		return DGXCOLOR(r + v.r, g + v.g, b + v.b, a + v.a);	}
DGXCOLOR DGXCOLOR::operator -(const DGXCOLOR& v) const{		return DGXCOLOR(r - v.r, g - v.g, b - v.b, a - v.a);	}
DGXCOLOR DGXCOLOR::operator *( FLOAT f)const		{		return DGXCOLOR(r * f  , g * f  , b * f  , a * f  );	}
DGXCOLOR DGXCOLOR::operator /( FLOAT f)const{FLOAT t=1.0F/f;return DGXCOLOR(r * t  , g * t  , b * t  , a * t  );	}
DGXCOLOR operator *(FLOAT f, const DGXCOLOR& v)	{			return DGXCOLOR(f * v.r, f * v.g, f * v.b, f * v.a);	}

//BOOL DGXCOLOR::operator == (const DGXCOLOR& v) const	{	return r == v.r && g == v.g && b == v.b && a == v.a;	}
//BOOL DGXCOLOR::operator != (const DGXCOLOR& v) const	{	return r != v.r || g != v.g || b != v.b || a != v.a;	}

BOOL DGXCOLOR::operator ==(const DGXCOLOR& v) const {	return IsEqual(r, v.r)    && IsEqual(g, v.g)    && IsEqual(b, v.b)    && IsEqual(a, v.a);		}
BOOL DGXCOLOR::operator !=(const DGXCOLOR& v) const {	return IsNotEqual(r, v.r) || IsNotEqual(g, v.g) || IsNotEqual(b, v.b) || IsNotEqual(a, v.a);	}



////////////////////////////////////////////////////////////////////////////////
// Plane

DGXPLANE::DGXPLANE()								{	a =0.F;	b = 0.F; c = 0.F;	d = 0.F;	}
DGXPLANE::DGXPLANE(const DGXPLANE& v)				{	a =v.a;	b = v.b; c = v.c;	d = v.d;	}
DGXPLANE::DGXPLANE(const FLOAT* v)					{	a =v[0];b = v[1];c = v[2];	d = v[3];	}
DGXPLANE::DGXPLANE( FLOAT A,FLOAT B,FLOAT C,FLOAT D){	a =A;	b = B;	 c = C;		d = D;		}

// casting
DGXPLANE::operator FLOAT* ()			{	return (FLOAT*) &a;			}
DGXPLANE::operator const FLOAT* () const{	return (const FLOAT*) &a;	}
FLOAT& DGXPLANE::operator[](INT n)		{	return *((&a)+ n);			}

// unary operators
DGXPLANE DGXPLANE::operator + () const	{	return *this;						}
DGXPLANE DGXPLANE::operator - () const	{	return DGXPLANE(-a, -b, -c, -d);	}

// binary operators
BOOL DGXPLANE::operator == (const DGXPLANE& p) const	{	return a == p.a && b == p.b && c == p.c && d == p.d;	}
BOOL DGXPLANE::operator != (const DGXPLANE& p ) const	{	return a != p.a || b != p.b || c != p.c || d != p.d;	}


void DGXPLANE::SetupFromPointNormal(const DGXVECTOR3* point, const DGXVECTOR3* normal)
{
	this->a  = normal->x;
	this->b  = normal->y;
	this->c  = normal->z;
	this->d  = - *point * *normal;
}


void DGXPLANE::SetupFromPoints(const DGXVECTOR3* p0, const DGXVECTOR3* p1, const DGXVECTOR3* p2)
{
	DGXVECTOR3	n = (*p1 - *p0) ^ (*p2 - *p0);
	n.Normalize();

	this->a  = n.x;
	this->b  = n.y;
	this->c  = n.z;
	this->d  = - *p0 * n;
}


FLOAT DGXVec3Dot(const DGXVECTOR3* p1, const DGXVECTOR3* p2)
{
	return (*p1) * (*p2);
}


FLOAT DGXVec3Length(const DGXVECTOR3* v)
{
	return (FLOAT)sqrt(	v->x * v->x +
						v->y * v->y +
						v->z * v->z		);
}


FLOAT DGXPlaneDotCoord(const DGXPLANE *pP, const DGXVECTOR3 *pV)
{
	return pP->a * pV->x + pP->b * pV->y + pP->c * pV->z + pP->d;
}




