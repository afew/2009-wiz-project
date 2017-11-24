//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	Type definition for LPH Applications.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Type_H_
#define _DGE_Type_H_


#define DGE_SDK_VER		0x00020000
#define DGE_SDK_DATE	0x20100818


typedef	short int			SHORT;
typedef	int					INT;
typedef	int					BOOL;
typedef	long int			LONG;
typedef	long int			HRESULT;
typedef float               FLOAT;
typedef double				DOUBLE;

typedef	unsigned char		BYTE;
typedef	unsigned short		WORD;
typedef	unsigned int		UINT;


#if defined(_WIN32) || defined(WIN32)
	typedef unsigned long	DWORD;
	typedef	unsigned short	wchar_t;
#else
	typedef unsigned int	DWORD;
	typedef	unsigned short	WCHAR;
#endif

typedef void*				LPVOID;



// for mobile solution.
typedef int					GFIXED;

typedef	void*				DGE_HANDLE;				// for mobile device
typedef	unsigned int		DGE_STATE;
typedef	int					DGE_DEVICE;				// Device Handle

typedef unsigned int		DGE_VERTEX_BUFFER;		// for VBO(Vertex Buffer Object)
typedef unsigned int		DGE_INDEX_BUFFER;		// for IBO(Index Buffer Object == VBO)


#ifndef CONST
#define CONST   const
#endif

#ifndef NULL
#define NULL	0
#endif

#ifndef BADBEEF
#define BADBEEF	0xBADBEEF
#endif

#ifndef BADFOOD
#define BADFOOD	0xBADF00D
#endif

#ifndef TRUE
#define TRUE	1
#endif

#ifndef FALSE
#define FALSE	0
#endif

#ifndef E_FAIL
#define E_FAIL	-1
#endif


#ifndef DGE_TRUE
#define DGE_TRUE	1
#endif

#ifndef DGE_FALSE
#define DGE_FALSE	0
#endif

#ifndef DGE_EFAIL
#define DGE_EFAIL	-1
#endif


#ifndef FILE_BEGIN
#define FILE_BEGIN		SEEK_SET
#define FILE_CURRENT	SEEK_CUR
#define FILE_END		SEEK_END
#endif

/* Minimum and maximum macros */
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#define __min(a,b)  (((a) < (b)) ? (a) : (b))


#define DGE_MAX_PATH   160
#define DGE_MAX_DRIVE  3
#define DGE_MAX_DIR    160
#define DGE_MAX_FNAME  160
#define DGE_MAX_EXT    8


#ifndef DGE_INLINE

	#if defined(_WIN32) || defined(WIN32)
		#define DGE_INLINE __inline
	#else
		#define DGE_INLINE inline __attribute__ ((always_inline))
	#endif

#endif


// Return Value
#ifndef DGE_SUCCEEDED
#define DGE_SUCCEEDED(hr) ((HRESULT)(hr) >= 0)
#define DGE_FAILED(hr) ((HRESULT)(hr) < 0)
#endif

#define DGE_DEFAULT	((UINT) -1)
#define DGE_OK						0x00000000
#define DGE_EFAIL					-1
#define DGE_EINVALIDATE_CALL		0XF0000001
#define DGE_ECANNOTALLOCATED		0XF0000002
#define DGE_ECANNOTFIND_RESOURCE	0XF0000003
#define DGE_ENOTIMPLEMENTED			0XF0000004
#define DGE_ECANNOTACQUIRE_DEVICE	0XF0000005
#define DGE_INVALID_DEVICE			-1



struct DGE_POINT2
{
	INT _x;	INT _y;

	DGE_POINT2() : _x(0), _y(0){}
	DGE_POINT2(INT X,INT Y) : _x(X), _y(Y){}
};

struct DGE_POINT3
{
	INT _x;	INT _y;	INT _z;

	DGE_POINT3() : _x(0), _y(0), _z(0){}
	DGE_POINT3(INT X,INT Y,INT Z) : _x(X), _y(Y), _z(Z){}
};

struct DGE_RECT
{
	union{	INT left; 	INT _x;	};
	union{	INT top;	INT _y;	};
	union{	INT right;	INT _w;	};
	union{	INT bottom;	INT _h;	};

	DGE_RECT() : _x(0), _y(0), _w(0), _h(0){}
	DGE_RECT(INT X,INT Y,INT W,INT H) : _x(X), _y(Y), _w(W), _h(H){}
};


struct DGE_SHORT2
{
	union{	struct{	SHORT x; SHORT y;	};	SHORT m[2];	};

	DGE_SHORT2() : x(0), y(0){}
	DGE_SHORT2(SHORT X,SHORT Y) : x(X), y(Y){}
};



#if defined(_WIN32) || defined(WIN32)
	#pragma pack(push, 2)
	struct DGE_SHORT3
	{
		union{	struct{ SHORT x; SHORT y; SHORT z;}; SHORT m[3]; };

		DGE_SHORT3() : x(0), y(0), z(0){}
		DGE_SHORT3(SHORT X,SHORT Y,SHORT Z) : x(X), y(Y), z(Z){}
	};
	#pragma pack(pop)

#else
	typedef struct tagDGE_SHORT3
	{
		SHORT x; SHORT y; SHORT z;

		tagDGE_SHORT3() : x(0), y(0), z(0){}
		tagDGE_SHORT3(SHORT X,SHORT Y,SHORT Z) : x(X), y(Y), z(Z){}
	} __attribute__((packed)) DGE_SHORT3;
#endif



struct DGE_INT2
{
	union{	struct	{	INT x; INT y;	};	INT	m[2];	};
	DGE_INT2() : x(0), y(0){}
	DGE_INT2(INT X,INT Y) : x(X), y(Y){}
};


struct DGE_INT3
{
	union{	struct	{	INT x; INT y; INT z;	};	INT	m[3];	};
	DGE_INT3() : x(0), y(0), z(0){}
	DGE_INT3(INT X,INT Y,INT Z) : x(X), y(Y), z(Z){}
};

struct DGE_INT4
{
	union{	struct	{	INT x; INT y; INT z; INT w;	};	INT	m[4];	};
	DGE_INT4() : x(0), y(0), z(0), w(0){}
	DGE_INT4(INT X,INT Y,INT Z,INT W) : x(X), y(Y), z(Z), w(W){}
};


struct DGE_FLOAT2
{
	union{	struct	{	FLOAT x; FLOAT y;	};	FLOAT m[2];	};
	DGE_FLOAT2() : x(0), y(0){}
	DGE_FLOAT2(FLOAT X,FLOAT Y) : x(X), y(Y){}
};


struct DGE_FLOAT3
{
	union{	struct	{	FLOAT x; FLOAT y; FLOAT z;	};	FLOAT m[3];	};
	DGE_FLOAT3() : x(0), y(0), z(0){}
	DGE_FLOAT3(FLOAT X,FLOAT Y,FLOAT Z) : x(X), y(Y), z(Z){}
};

struct DGE_FLOAT4
{
	union{	struct	{	FLOAT x; FLOAT y; FLOAT z; FLOAT w;	};	FLOAT m[4];	};
	DGE_FLOAT4() : x(0), y(0), z(0), w(0){}
	DGE_FLOAT4(FLOAT X,FLOAT Y,FLOAT Z,FLOAT W) : x(X), y(Y), z(Z), w(W){}
};


struct DGE_COLORB
{
	union{	struct{	BYTE r; BYTE g; BYTE b; BYTE a;	};	BYTE m[4];	};
	DGE_COLORB() : r(0), g(0), b(0), a(0){}
	DGE_COLORB(BYTE R,BYTE G,BYTE B,BYTE A) : r(R), g(G), b(B), a(A){}
};


struct DGE_COLORF
{
	union{	struct{	FLOAT r; FLOAT g; FLOAT b; FLOAT a;	};	FLOAT m[4];	};
	DGE_COLORF() : r(0), g(0), b(0), a(0){}
	DGE_COLORF(FLOAT R,FLOAT G,FLOAT B,FLOAT A) : r(R), g(G), b(B), a(A){}
};


struct DGE_MATRIX
{
	union
	{
		struct
		{
			FLOAT _11, _12, _13, _14;
			FLOAT _21, _22, _23, _24;
			FLOAT _31, _32, _33, _34;
			FLOAT _41, _42, _43, _44;

		};
		FLOAT m[4][4];
	};

	DGE_MATRIX(): _11(1), _12(0), _13(0), _14(0)
				, _21(0), _22(1), _23(0), _24(0)
				, _31(0), _32(0), _33(1), _34(0)
				, _41(0), _42(0), _43(0), _44(1)
			{}

	DGE_MATRIX(FLOAT t11, FLOAT t12, FLOAT t13, FLOAT t14
			,  FLOAT t21, FLOAT t22, FLOAT t23, FLOAT t24
			,  FLOAT t31, FLOAT t32, FLOAT t33, FLOAT t34
			,  FLOAT t41, FLOAT t42, FLOAT t43, FLOAT t44
			):_11(t11), _12(t12), _13(t13), _14(t14)
			, _21(t21), _22(t22), _23(t23), _24(t24)
			, _31(t31), _32(t32), _33(t33), _34(t34)
			, _41(t41), _42(t42), _43(t43), _44(t44)
			{}

};


// for Window Application
typedef UINT		WPARAM;
typedef LONG		LPARAM;
typedef LONG		LRESULT;

#if defined(_WIN32) || defined(WIN32)
	#ifndef DGE_CALLBACK
	#define DGE_CALLBACK	__stdcall
	#endif

	#ifndef DGE_WINAPI
	#define DGE_WINAPI		__stdcall
	#endif
#else
	#ifndef DGE_CALLBACK
	#define DGE_CALLBACK
	#endif

	#ifndef DGE_WINAPI
	#define DGE_WINAPI
	#endif

	struct HWND__ { int unused; };

#endif


#if defined(_WIN32) || defined(WIN32)
typedef struct HWND__*	DGE_HWND;
#else
typedef void*			DGE_HWND;
#endif


// Interface define
#ifndef interface
	#define interface struct
#endif

#ifndef DGE_CLASS_DESTROYER
	#define DGE_CLASS_DESTROYER( CLASS_NAME )	\
	virtual ~CLASS_NAME(){}
#endif



#endif	//_DGE_Type_H_




