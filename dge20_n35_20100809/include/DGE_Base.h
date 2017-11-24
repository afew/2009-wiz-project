//	Copyright(C) Gamepark Holdings. All rights reserved.
//	Dogma-G Game Studios In-House Library DGE
//
//	for 3D Rendering Pipe Line.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER > 1000
	#pragma once
	#endif
#endif


#ifndef _DGE_Base_H_
#define _DGE_Base_H_

#include <DGE_Type.h>


// Device
////////////////////////////////////////////////////////////////////////////////

enum EDGE_DEVICE_ST
{
	DGE_CLEAR_COLOR_BUFFER	= 0x00004000,	// GL_COLOR_BUFFER_BIT
	DGE_CLEAR_DEPTH_BUFFER	= 0x00000100,	// GL_DEPTH_BUFFER_BIT
	DGE_CLEAR_STENCIL_BUFFER= 0x00000400,	// GL_STENCIL_BUFFER_BIT
};

// Vertex Format for Fixed Pipe Line
enum EDGE_DEVICE_FORMAT
{
	DGE_FVF_XYZ			= 0x01,		//	1<<0
	DGE_FVF_NORMAL		= 0x02,		//	1<<1
	DGE_FVF_DIFFUSE		= 0x04,		//	1<<2
	DGE_FVF_TEX1		= 0x08,		//	1<<3

	DGE_FMT_INDEX16		= 0x1403,	// GL_UNSIGNED_SHORT
	DGE_FMT_INDEX32		= 0x140C,	// GL_FIXED
	DGE_FMT_UBYTE		= 0x1401,	// GL_UNSIGNED_BYTE
	DGE_FMT_FLOAT		= 0x1406,	// GL_FLOAT
	DGE_FMT_FIXED		= 0x140C,	// GL_FIXED
};

enum EDGE_TRANSFORM
{
	DGE_TS_WORLD		= 0x0001,
	DGE_TS_VIEW			= 0x0002,
	DGE_TS_PROJ			= 0x0003,
};

enum EDGE_PRIMITIVETYPE
{
	DGE_PT_POINT_LIST		=  0x0000,	// GL_POINTS
	DGE_PT_LINE_LIST		=  0x0001,	// GL_LINES
	DGE_PT_LINE_LOOP		=  0x0002,	// GL_LINE_LOOP
	DGE_PT_LINE_STRIP		=  0x0003,	// GL_LINE_STRIP
	DGE_PT_TRIANGLE_LIST	=  0x0004,	// GL_TRIANGLES
	DGE_PT_TRIANGLE_STRIP	=  0x0005,	// GL_TRIANGLE_STRIP
	DGE_PT_TRIANGLE_FAN		=  0x0006,	// GL_TRIANGLE_FAN
};


// Rendering State
enum EDGE_RENDERINGSTATE
{									// Status(Value)
	DGE_RS_CLEAR_COLOR	= 0x010000,	// glClearColor() Set
	DGE_RS_SHADE_MODEL	= 0x010001,	// Flat, Smooth
	DGE_RS_DEPTH_TEST	= 0x0B71,	// GL_DEPTH_TEST. Enable(True), Disable(False)
	DGE_RS_CULL_FACE	= 0x0B44,	// GL_CULL_FACE, Enable(True), Disable(False), glCullFace()
	DGE_RS_CULL_MODE	,			// glFrontFace(),

	DGE_RS_BLEND		= 0x0BE2,	// GL_BLEND: AlphaBlending Enable, Disable
	DGE_RS_BLEND_SRC	,			// glBlendFunc(Source, ...): Default GL_SRC_ALPHA
	DGE_RS_BLEND_DEST	,			// glBlendFunc(..., Dest): Default GL_ONE_MINUS_SRC_ALPHA

	DGE_RS_FOG			= 0x0B60,	// glEnable(GL_FOG), glDisable(GL_FOG)
	DGE_RS_FOG_DATA		,			// glFogf...(), GL_FOG_COLOR, GL_FOG_MODE, GL_FOG_START, GL_FOG_END  Set

	DGE_RS_LIGHTING		= 0x0B50,	// glEnable(GL_LIGHTING), glDisable(GL_LIGHTING)
	DGE_RS_LIGHT0		= 0x4000,	// GL_LIGHT0
	DGE_RS_LIGHT1		= 0x4001,	// GL_LIGHT1
	DGE_RS_LIGHT2		= 0x4002,	// GL_LIGHT2
	DGE_RS_LIGHT3		= 0x4003,	// GL_LIGHT3
	DGE_RS_LIGHT4		= 0x4004,	// GL_LIGHT4
	DGE_RS_LIGHT5		= 0x4005,	// GL_LIGHT5
	DGE_RS_LIGHT6		= 0x4006,	// GL_LIGHT6
	DGE_RS_LIGHT7		= 0x4007,	// GL_LIGHT7
	DGE_RS_LIGHT0_DATA	,			// glLightfv(GL_LIGHT0, ...)
	DGE_RS_LIGHT1_DATA	,			// glLightfv(GL_LIGHT1, ...)
	DGE_RS_LIGHT2_DATA	,			// glLightfv(GL_LIGHT2, ...)
	DGE_RS_LIGHT3_DATA	,			// glLightfv(GL_LIGHT3, ...)
	DGE_RS_LIGHT4_DATA	,			// glLightfv(GL_LIGHT4, ...)
	DGE_RS_LIGHT5_DATA	,			// glLightfv(GL_LIGHT5, ...)
	DGE_RS_LIGHT6_DATA	,			// glLightfv(GL_LIGHT6, ...)
	DGE_RS_LIGHT7_DATA	,			// glLightfv(GL_LIGHT7, ...)
	DGE_RS_MATERIAL_DATA,			// glLightfv(GL_LIGHT7, ...)
};

// Rendering Status(State Value)
enum EDGE_RENDERINGSTATUS
{
	DGE_ST_ENABLE				= 0x0001, // True
	DGE_ST_DISABLE				= 0x0000, // False

	DGE_ST_ZERO					= 0x0000, // GL_ZERO
	DGE_ST_ONE					= 0x0001, // GL_ONE

	DGE_ST_NEVER				= 0x0200, // GL_NEVER
	DGE_ST_LESS					= 0x0201, // GL_LESS
	DGE_ST_EQUAL				= 0x0202, // GL_EQUAL
	DGE_ST_LEQUAL				= 0x0203, // GL_LEQUAL
	DGE_ST_GREATER				= 0x0204, // GL_GREATER
	DGE_ST_NOTEQUAL				= 0x0205, // GL_NOTEQUAL
	DGE_ST_GEQUAL				= 0x0206, // GL_GEQUAL
	DGE_ST_ALWAYS				= 0x0207, // GL_ALWAYS

	DGE_ST_FLAT					= 0x1D00, // GL_FLAT
	DGE_ST_SMOOTH				= 0x1D01, // GL_SMOOTH

	DGE_ST_CW					= 0x0900, // GL_CW
	DGE_ST_CCW					= 0x0901, // GL_CCW
	DGE_ST_FRONT				= 0x0404, // GL_FRONT
	DGE_ST_BACK					= 0x0405, // GL_BACK
	DGE_ST_FRONT_AND_BACK		= 0x0408, // GL_FRONT_AND_BACK
	DGE_ST_CULL_FACE			= 0x0B44, // GL_CULL_FACE
	DGE_ST_POLYGON_OFFSET_FILL	= 0x8037, // GL_POLYGON_OFFSET_FILL

	DGE_ST_SRC_COLOR			= 0x0300, // GL_SRC_COLOR
	DGE_ST_ONE_MINUS_SRC_COLOR	= 0x0301, // GL_ONE_MINUS_SRC_COLOR
	DGE_ST_SRC_ALPHA			= 0x0302, // GL_SRC_ALPHA
	DGE_ST_ONE_MINUS_SRC_ALPHA	= 0x0303, // GL_ONE_MINUS_SRC_ALPHA
	DGE_ST_DST_ALPHA			= 0x0304, // GL_DST_ALPHA
	DGE_ST_ONE_MINUS_DST_ALPHA	= 0x0305, // GL_ONE_MINUS_DST_ALPHA
	DGE_ST_DST_COLOR			= 0x0306, // GL_DST_COLOR
	DGE_ST_ONE_MINUS_DST_COLOR	= 0x0307, // GL_ONE_MINUS_DST_COLOR
	DGE_ST_SRC_ALPHA_SATURATE	= 0x0308, // GL_SRC_ALPHA_SATURATE

	DGE_ST_FOG_LINEAR			= 0x2601, // GL_LINEAR
	DGE_ST_GL_EXP				= 0x0800, // GL_EXP
	DGE_ST_GL_EXP2				= 0x0801, // GL_EXP2

	DGE_ST_AMBIENT				= 0x1200, // GL_AMBIENT
	DGE_ST_DIFFUSE				= 0x1201, // GL_DIFFUSE
	DGE_ST_SPECULAR				= 0x1202, // GL_SPECULAR
	DGE_ST_POSITION				= 0x1203, // GL_POSITION
	DGE_ST_SPOT_DIRECTION		= 0x1204, // GL_SPOT_DIRECTION
	DGE_ST_SPOT_EXPONENT		= 0x1205, // GL_SPOT_EXPONENT
	DGE_ST_SPOT_CUTOFF			= 0x1206, // GL_SPOT_CUTOFF
	DGE_ST_CONSTANT_ATTENUATION	= 0x1207, // GL_CONSTANT_ATTENUATION
	DGE_ST_LINEAR_ATTENUATION	= 0x1208, // GL_LINEAR_ATTENUATION
	DGE_ST_QUADRATIC_ATTENUATION= 0x1209, // GL_QUADRATIC_ATTENUATION
	DGE_ST_EMISSION				= 0x1600, // GL_EMISSION
	DGE_ST_SHININESS			= 0x1601, // GL_SHININESS
};



enum EDGE_TEXTURE_STATE
{
	DGE_TS_TEXTURE_ENV_MODE			= 0x2200, // GL_TEXTURE_ENV_MODE
	DGE_TS_TEXTURE_MAG_FILTER		= 0x2800, // GL_TEXTURE_MAG_FILTER
	DGE_TS_TEXTURE_MIN_FILTER		= 0x2801, // GL_TEXTURE_MIN_FILTER
	DGE_TS_TEXTURE_WRAP_S			= 0x2802, // GL_TEXTURE_WRAP_S
	DGE_TS_TEXTURE_WRAP_T			= 0x2803, // GL_TEXTURE_WRAP_T
	DGE_TS_TEXTURE_ENV_COLOR		= 0x2201, // GL_TEXTURE_ENV_COLOR
	DGE_TS_MODULATE					= 0x2100, // GL_MODULATE
	DGE_TS_DECAL					= 0x2101, // GL_DECAL
	DGE_TS_ADD						= 0x0104, // GL_ADD
	DGE_TS_ADD_SIGNED				= 0x8574, // GL_ADD_SIGNED
	DGE_TS_SUBTRACT					= 0x84E7, // GL_SUBTRACT
	DGE_TS_INTERPOLATE				= 0x8575, // GL_INTERPOLATE
	DGE_TS_NEAREST					= 0x2600, // GL_NEAREST
	DGE_TS_LINEAR					= 0x2601, // GL_LINEAR
	DGE_TS_NEAREST_MIPMAP_NEAREST	= 0x2700, // GL_NEAREST_MIPMAP_NEAREST
	DGE_TS_LINEAR_MIPMAP_NEAREST	= 0x2701, // GL_LINEAR_MIPMAP_NEAREST
	DGE_TS_NEAREST_MIPMAP_LINEAR	= 0x2702, // GL_NEAREST_MIPMAP_LINEAR
	DGE_TS_LINEAR_MIPMAP_LINEAR		= 0x2703, // GL_LINEAR_MIPMAP_LINEAR
	DGE_TS_REPEAT					= 0x2901, // GL_REPEAT
	DGE_TS_CLAMP					= 0x812F, // GL_CLAMP_TO_EDGE
};


typedef struct tagTDGE_FOG
{
	DGE_COLORF	FogColor;		// FLOAT r,g,b,a
	FLOAT		FogMode;		// DGE_ST_FOG_LINEAR
	FLOAT		FogBegin;		// Fog start
	FLOAT		FogEnd;			// Fog End
} TDGE_FOG;


typedef struct tagTDGE_LIGHT	// DGE Lighting
{
	DGE_COLORF	Amb;			// Ambient Color
	DGE_COLORF	Dif;			// Diffuse Color
	DGE_COLORF	Spc;			// Specular Color
	DGE_FLOAT4	Pos;			// Lighting Position
	DGE_FLOAT4	Dir;			// Spot Direction
	FLOAT		Spe;			// Spot Exponent
	FLOAT		Cut;			// Spot Cut off
	FLOAT		Att0;			// Constant Attenuation
	FLOAT		Att1;			// Linear Attenuation
	FLOAT		Att2;			// Quadratic Attenuation
} TDGE_LIGHT;


typedef struct tagTDGE_MATERIAL		// DGE Material
{
	INT			Fce;				// Face
	DGE_COLORF	Amb;				// Ambient
	DGE_COLORF	Dif;				// Diffuse
	DGE_COLORF	Spc;				// Specular
	DGE_COLORF	Ems;				// Emissive
	FLOAT		Shp;				// Sharpness
} TDGE_MATERIAL;




// Texture
interface	IDGE_Texture;
typedef		IDGE_Texture*	PDGE_TEXTURE;

// Vertex Buffer
interface	IDGE_VB;
typedef		IDGE_VB*	PDGE_VB;

// Index Buffer
interface	IDGE_IB;
typedef		IDGE_IB*	PDGE_IB;



// Draw Primitive.
// Position, Normal, and Texture Coordiante are Float. Color is unsigned byte.
//
INT DGE_DrawPrimitiveUPf(INT dFVF					// DGE_FVF
						 , INT nMode				// Primitive Type
						 , INT First				// Start Vertex Index
						 , INT nVertexCount			// Vertex Number
						 , const void* pVtx			// Vertex Stream
						 , INT dStride				// sizeof One Vertex
						 );

// Draw Indexed Primitive.
// Position, Normal, and Texture Coordiante are Float. Color is unsigned byte.
// Index buffer type is unsigned short.
//
INT DGE_DrawIndexedPrimitiveUPf(INT dFVF			// DGE_FVF
							, INT nMode				// Primitive Type
							, INT nIndexCount		// Number of Index
							, const void *indices	// Index data Stream
							, const void* pVtx		// Vertex data Stream
							, INT dStride			// sizeof One Vertex
							);

// Draw Primitive.
// all data type in vertex stream is Fixed.
//
INT DGE_DrawPrimitiveUPi(INT dFVF					// DGE_FVF
						 , INT nMode				// Primitive Type
						 , INT First				// Start Vertex Index
						 , INT nVertexCount			// Vertex Number
						 , const void* pVertices	// Vertex Stream
						 , INT dStride				// sizeof One Vertex
						 );

// Draw Indexed Primitive.
// all data type in vertex stream is Fixed.
// Index buffer type is unsigned short.
//
INT DGE_DrawIndexedPrimitiveUPi(INT dFVF			// DGE_FVF
							, INT nMode				// Primitive Type
							, INT nIndexCount		// Number of Index
							, const void *indices	// Index data Stream
							, const void* pVertices	// Vertex data Stream
							, INT dStride			// sizeof One Vertex
							);


interface IDGE_Device
{
	DGE_CLASS_DESTROYER(	IDGE_Device	);

	// 3D PipeLine World, View, Projection Transform
	virtual	INT		SetTransform(INT nTransform, const DGE_HANDLE Val)=0;
	virtual	INT		GetTransform(INT nTransform, DGE_HANDLE Val)=0;
	virtual	INT		SetTransformIdentity(INT nTransform)=0;


	virtual	INT		BeginScene()=0;										// Prepare Rendering
	virtual	INT		EndScene()=0;										// Post Rendering


	// Rendering State
	virtual	INT		SetRenderState(INT nState, INT v)=0;				// Redering Machine State
	virtual	INT		SetRenderState(INT nState, void* v)=0;				// Redering Machine State for Pointer
	virtual	INT		SetStatusEnable(INT nStatus)=0;						// Wrapping glEnable()
	virtual	INT		SetStatusDisable(INT nStatus)=0;					// Wrapping glDisable()


	// Texture and Multi-texture...
	virtual INT		SetTextureEnv(INT v1, FLOAT v2)=0;					// glTexEnvf(GL_TEXTURE_ENV, ..., ...)

	virtual INT		SetTextureAddressS (INT nState, INT v)=0;
	virtual INT		SetTextureAddressT (INT nState, INT v)=0;
	virtual INT		SetTextureFilterMin(INT nState, INT v)=0;
	virtual INT		SetTextureFilterMag(INT nState, INT v)=0;
	virtual INT		SetTextureStageOp  (INT nState, INT v)=0;


	// Vertex Format
	virtual	INT		SetFVF(INT nFVF)=0;

	// Set Texture
	virtual INT		SetTexture(INT nState, PDGE_TEXTURE pTex)=0;


	// Color Setting...
	virtual	INT		SetColor(FLOAT r,FLOAT g,FLOAT b,FLOAT a=1.f)=0;	// glColor4f()
	virtual	INT		SetColor(FLOAT* v)=0;								// glColor4v()


	// Rendering Primitive for Vertex Buffer Object
	virtual INT		SetStreamSource(PDGE_VB)=0;
	virtual INT		SetIndices(PDGE_IB)=0;
	virtual INT		DrawPrimitivef()=0;
	virtual INT		DrawIndexedPrimitivef(INT nMode, INT nCount)=0;


	// Rendering Primitive for User Memory Pointer
	virtual INT		DrawPrimitiveUPf(INT nMode, INT First, INT nVertexCount, const void* pVertices, INT nStride)=0;
	virtual INT		DrawIndexedPrimitiveUPf(INT nMode, INT nIndexCount, const void *indices, const void* pVertices, INT dStride)=0;

	virtual INT		DrawPrimitiveUPi(INT nMode, INT First, INT nVertexCount, const void* pVertices, INT nStride)=0;
	virtual INT		DrawIndexedPrimitiveUPi(INT nMode, INT nIndexCount, const void *indices, const void* pVertices, INT dStride)=0;


	virtual INT		Clear(DWORD dClearMode) =0;														// glClear()
	virtual INT		Present(DGE_HANDLE =0, DGE_HANDLE  =0, DGE_HANDLE =0, DGE_HANDLE =0)=0;			// glSwapBuffer() + glFlush()




	// Application Data Interface.
	virtual DGE_HANDLE	GetMainApp	()=0;	// Main Application Pointer
	virtual DGE_HANDLE	GetSprite	()=0;	// 2D Sprite Pointer
	virtual DGE_HANDLE	GetInput	()=0;	// Input Pointer
	virtual DGE_HANDLE	GetNetwork	()=0;	// Network Pointer
	virtual DGE_HANDLE	GetUserData1()=0;	// User Data Pointer 1
	virtual DGE_HANDLE	GetUserData2()=0;	// User Data Pointer 2
	virtual DGE_HANDLE	GetUserData3()=0;	// User Data Pointer 3
	virtual DGE_HANDLE	GetUserData4()=0;	// User Data Pointer 4

	virtual void	SetMainApp	(DGE_HANDLE)=0;
	virtual void	SetSprite	(DGE_HANDLE)=0;
	virtual void	SetInput	(DGE_HANDLE)=0;
	virtual void	SetNetwork	(DGE_HANDLE)=0;
	virtual void	SetUserData1(DGE_HANDLE)=0;
	virtual void	SetUserData2(DGE_HANDLE)=0;
	virtual void	SetUserData3(DGE_HANDLE)=0;
	virtual void	SetUserData4(DGE_HANDLE)=0;
};


typedef	IDGE_Device*	PDGE_DEVICE;


// Create Device
INT DGE_CreateDevice(char* sCmd
					   , PDGE_DEVICE* pData
					   , DGE_HANDLE p1			// Window Handle
					   , DGE_HANDLE p2			// Main Application Program Pointer
					   , DGE_HANDLE p3 = NULL	// No Use
					   , DGE_HANDLE p4 = NULL	// No Use
					 );

// Destroy Device
INT DGE_DestroyDevice(PDGE_DEVICE* pData);





// Sprite
////////////////////////////////////////////////////////////////////////////////

interface IDGE_Sprite
{
	DGE_CLASS_DESTROYER(	IDGE_Sprite	);

	virtual INT		Begin(DWORD dMode=0)=0;				// Sprite를 실행하기 전에 환경 설정
	virtual INT		End()=0;							// 저장되어 있는 환경 반환


	virtual INT		Draw( PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
						, const DGE_RECT*	pImgRc		// Image rect
						, const DGE_FLOAT2* vcTrn		// Position
						, const DGE_COLORF*	Color=NULL	// color
						)=0;

	virtual INT		DrawEx(PDGE_TEXTURE		pTexture	// DGE_Texture Pointer
						, const DGE_RECT*	pImgRc		// Image rect
						, const DGE_FLOAT2*	vcScl		// Scaling
						, const DGE_FLOAT2*	vcRot		// Rotation Center
						, FLOAT				fRot		// Angle(Radian)
						, const DGE_FLOAT2* vcTrn		// Position
						, const DGE_COLORF*	Color=NULL	// color
						) = 0;
};

typedef	IDGE_Sprite*	PDGE_SPRITE;

// Create Sprite
INT DGE_CreateSprite(char* sCmd
					   , PDGE_SPRITE* pData
					   , DGE_HANDLE p1			// IDGE_Device*
					   , DGE_HANDLE p2 = NULL	// No Use
					   , DGE_HANDLE p3 = NULL	// No Use
					   , DGE_HANDLE p4 = NULL	// No Use
					 );

// Destroy Sprite
INT DGE_DestroySprite(PDGE_SPRITE* pData);





// Image
////////////////////////////////////////////////////////////////////////////////

enum EDGE_IMAGE_RSC
{
	DGE_IMG_UNKNOWN	= 0	,
	DGE_IMG_BMP	= 0x2	,
	DGE_IMG_TGA	= 0x3	,
	DGE_IMG_PNG	= 0x4	,

#if defined(_WIN32) || defined(WIN32)
	DGE_IMG_JPG	= 0x5	,	// Only Window Application
#endif

	DGE_IMG_GPT	= 0x6	,	// for Wiz, Caanoo...

	DGE_IMG_MAX_WIDTH	= 512,	// Image max width
	DGE_IMG_MAX_HEIGHT	= 512,	// Image max Height
};


enum EDGE_PIXEL_FORMAT
{
	DGE_FMT_ALPHA			= 0x1906,	// GL_ALPHA
	DGE_FMT_RGB				= 0x1907,	// GL_RGB
	DGE_FMT_RGBA			= 0x1908,	// GL_RGBA
	DGE_FMT_LUMINANCE		= 0x1909,	// GL_LUMINANCE
	DGE_FMT_LUMINANCE_ALPHA	= 0x190A,	// GL_LUMINANCE_ALPHA
	DGE_FMT_WORD_565		= 0x8363,	// GL_UNSIGNED_SHORT_5_6_5
	DGE_FMT_WORD_5551		= 0x8034,	// GL_UNSIGNED_SHORT_5_5_5_1
	DGE_FMT_WORD_4444		= 0x8033,	// GL_UNSIGNED_SHORT_4_4_4_4
};



struct TDGE_IMAGE
{
	UINT	Format;				// Image Format
	UINT	Type;				// Image Type

	UINT	ImgW;				// Image Width
	UINT	ImgH;				// Image Height
	UINT	ImgD;				// Image Depth
	DWORD	ImgC;				// Image Color Key

	BYTE*	pPxl;				// pixel
};


interface IDGE_Image
{
	DGE_CLASS_DESTROYER(	IDGE_Image	);

	virtual UINT	GetRscType()=0;					// Resource File Format BMP, TGA, PNG, GPT
	virtual UINT	GetFormat()=0;					// Pixel Format. only GPT. → GL_RGB, RGBA, LUMINANCE, LUMINANCE_ALPHA
	virtual UINT	GetType()=0;					// Pixel Type. only GPT. → UNSIGNED_SHORT565, UNSIGNED_SHORT4444, UNSIGNED_SHORT5551

	virtual UINT	GetImgW()=0;					// Image Width
	virtual UINT	GetImgH()=0;					// Image Height
	virtual UINT	GetImgD()=0;					// Image Depth(Channel). 1,2,3, and 4 (byte)
	virtual UINT	GetImgC()=0;					// Image Color Key. only GPT.
	virtual BYTE*	GetPixel()=0;					// Pixel data

	virtual INT		SaveToFile(char* sFile			// Pixel data Save to TGA or GPT
							, INT ImgType=DGE_IMG_GPT)=0;
};

typedef	IDGE_Image*	PDGE_IMAGE;

// Create Image
INT DGE_CreateImage(char* sCmd						// Null is File, "Buffer" is Memory buffer.
					   , PDGE_IMAGE* pData
					   , DGE_HANDLE p1				// sCmd => NULL →File Name, "Resource" →Resource ID, "Buffer" → Buffer Width
					   , DGE_HANDLE p2				// "Buffer" → Buffer Height
					   , DGE_HANDLE p3 = NULL		// Color Key
					   , DGE_HANDLE p4 = NULL		// No Use
					 );

// Destroy Image
INT DGE_DestroyImage(PDGE_IMAGE* pData);




// Convert 32 or 24 Bit to 16 Bit Color
//	Color Key: 0x00000000 → disable the colorkey
//	Channel == 3
//		Color Key disable → GL_UNSIGNED_SHORT_5_6_5
//		Color Key enable  → GL_UNSIGNED_SHORT_5_5_5_1
//	Channel == 4
//		regardless of Color Key → GL_UNSIGNED_SHORT_4_4_4_4
INT	DGE_Convert32to16Color(WORD* pDst
						   , UINT* pOutFormat		// EDGE_PIXEL_FORMAT
						   , UINT* pOutType			// EDGE_PIXEL_FORMAT

						   , const BYTE* pInSrc
						   , INT nInImgW
						   , INT nInImgH
						   , INT nInImgD
						   , DWORD dInColorKey);



// Texture
////////////////////////////////////////////////////////////////////////////////

interface IDGE_Texture
{
	DGE_CLASS_DESTROYER(	IDGE_Texture	);

	virtual const char* const GetName()const=0;		// Resource Name
	virtual UINT	GetId()=0;						// OpenGL ID
	virtual UINT	GetFormat()=0;					// Pixel Format rgb, rgba, luminance...
	virtual UINT	GetType()=0;					// Pixel Type	u_short 565, 5551, 4444

	virtual UINT	GetImgW()=0;					// Image Width
	virtual UINT	GetImgH()=0;					// Image Height
	virtual UINT	GetImgD()=0;					// Image Depth
	virtual DWORD	GetImgC()=0;					// Image ColorKey

	virtual	void	SetOwner(void*)=0;				// Setting Owner. if Owner Exist. Texture instance cannot be destroyed.
	virtual	void*	GetOwner()=0;

	virtual	INT		BindTexture(INT modulate=0		// Binding Texture: If moduate =0  then Release Binding
							, INT filter_min=DGE_TS_LINEAR	// Minification Filter. GL_LINEAR: 0x2601
							, INT filter_mag=DGE_TS_LINEAR	// Magnification Filter
							, INT smp_addrS=DGE_TS_REPEAT	// Texture Address mode for the S coordinate. GL_REPEAT: 0x2901
							, INT smp_addrT=DGE_TS_REPEAT	// Texture Address mode for the T coordinate
							)=0;



	virtual	INT		CopyTexImage2D()=0;				// glCopyImage2D: Copy to Texture from Frame Buffer
};

// Create Texture from File or Buffer and Rendering Copy Texture
// Ex) From File:         DGE_CreateTexture(NULL, &OutputTexture, (DGE_HANDLE)"File Name", NULL, &ColorKey(→Option) );
//     From Buffer:       DGE_CreateTexture(NULL, &OutputTexture, NULL, &TDGE_IMAGE Address(pointer));
//
//     Rendering Texture: DGE_CreateTexture(NULL, &OutputTexture, NULL, NULL, &(int)Image_Width, &(int)Image_Height);

INT DGE_CreateTexture(char* sCmd				// Null is File, "Buffer" is Memory buffer.
					   , PDGE_TEXTURE* pData
					   , DGE_HANDLE p1			// "File Name"
					   , DGE_HANDLE p2 = NULL	// Buffer Address. Need(if p1 == NULL)
					   , DGE_HANDLE p3 = NULL	// Color Key. Need DWORD address. if p1== NULL, p2 == NULL then It will be Rendering Copy Texture. so p3 is Image Width.
					   , DGE_HANDLE p4 = NULL	// Only Rendering Copy Texture Image Height
					 );
// Destroy Texture
INT DGE_DestroyTexture(PDGE_TEXTURE* pData);





// Vertex Buffer Data
////////////////////////////////////////////////////////////////////////////////

interface IDGE_VB
{
	DGE_CLASS_DESTROYER(	IDGE_VB	);

	virtual INT		Fill(DGE_HANDLE pBuf, INT nBufSize, BOOL bReCreateVB=FALSE)=0;	// Fill Buffer
	virtual INT		Bind(BOOL bBind=TRUE)=0;										// Bind Buffer
	virtual	void	SetOwner(DGE_HANDLE)=0;	// Setting Owner. if Owner Exist. Texture instance cannot be destroyed.
	virtual	void*	GetOwner()=0;
};


// Create Vertex Buffer Instance
INT DGE_CreateVB(char* sCmd
				   , PDGE_VB* pData
				   , DGE_HANDLE p1			// PDGE_DEVICE
				   , DGE_HANDLE p2			// Input FVF
				   , DGE_HANDLE p3 = NULL	// Input Buffer pointer
				   , DGE_HANDLE p4 = NULL	// Input Buffer Size(Byte)
					 );

// Destroy VB Instance
INT DGE_DestroyVB(PDGE_VB* pData);



// Index Buffer Data
////////////////////////////////////////////////////////////////////////////////

interface IDGE_IB
{
	DGE_CLASS_DESTROYER(	IDGE_IB	);

	virtual INT		Fill(DGE_HANDLE pBuf, INT nBufSize, BOOL bReCreateIB=FALSE)=0;	// Fill Buffer
	virtual INT		Bind(BOOL bBind=TRUE)=0;										// Bind Buffer
	virtual	void	SetOwner(DGE_HANDLE)=0;											// Setting Owner. if Owner Exist. Texture instance cannot be destroyed.
	virtual	void*	GetOwner()=0;
	virtual UINT	GetFmt()=0;														// Get Format
};

// Create Vertex Buffer Instance
INT DGE_CreateIB(char* sCmd
				   , PDGE_IB* pData
				   , DGE_HANDLE p1			// PDGE_DEVICE
				   , DGE_HANDLE p2			// Input FVF
				   , DGE_HANDLE p3 = NULL	// Input Buffer pointer
				   , DGE_HANDLE p4 = NULL	// Input Buffer Size(Byte)
					 );

// Destroy IB Instance
INT DGE_DestroyIB(PDGE_IB* pData);




// Application Frame
////////////////////////////////////////////////////////////////////////////////

interface IDGE_AppFrame
{
	DGE_CLASS_DESTROYER(	IDGE_AppFrame	);

	virtual INT		Init()=0;
	virtual INT		Run()=0;
	virtual INT		Query(char* Cmd, void* Value)=0;

	virtual INT		Create(DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL, DGE_HANDLE =NULL)=0;
	virtual INT		Destroy()=0;
	virtual INT		FrameMove()=0;
	virtual INT		Render()=0;
};

typedef	IDGE_AppFrame*	PDGE_APPFRAME;





// 3D Application Auxiliary
////////////////////////////////////////////////////////////////////////////////

// DGE 3D Index, Vertex Format

namespace DGE3D
{
	// 16-bit Triangle Index Stream
	#if defined(_WIN32) || defined(WIN32)

		#pragma pack(push, 2)
		struct VtxIdxW
		{
			union{	struct{ WORD a; WORD b; WORD c;}; WORD m[3]; };

			VtxIdxW() : a(0), b(1), c(2){}
			VtxIdxW(WORD A,WORD B,WORD C) : a(A), b(B), c(C){}
			VtxIdxW(const WORD* v)	{ a = v[0]; b = v[1]; c = v[2];	}

			operator WORD*()			{	return (WORD*)&a;		}
			operator const WORD*() const{	return (const WORD*)&a;	}

			enum { FVF = (DGE_FMT_INDEX16), };
		};
		#pragma pack(pop)

	#else

		typedef struct tagVtxIdxW
		{
			WORD a;
			WORD b;
			WORD c;

			tagVtxIdxW() : a(0), b(1), c(2){}
			tagVtxIdxW(WORD A,WORD B,WORD C) : a(A), b(B), c(C){}

			operator WORD*()			{	return (WORD*)&a;		}
			operator const WORD*() const{	return (const WORD*)&a;	}

			enum { FVF = (DGE_FMT_INDEX16), };
		} __attribute__((packed)) VtxIdxW;

	#endif

	// 32-bit FIXED Triangle Index Stream
	struct VtxIdxF
	{
		union{	struct{ GFIXED a; GFIXED b; GFIXED c;}; GFIXED m[3]; };

		VtxIdxF() : a(0), b(1), c(2){}
		VtxIdxF(INT A,INT B,INT C) : a(A<<16), b(B<<16), c(C<<16){};
		VtxIdxF(const GFIXED* v)	{ a = v[0]; b = v[1]; c = v[2];	}

		operator GFIXED*()			{	return (GFIXED*)&a;		}
		operator const GFIXED*() const{	return (const GFIXED*)&a;	}

		enum { FVF = (DGE_FMT_INDEX32), };
	};



	////////////////////////////////////////////////////////////////////////////
	// Fixed Type

	struct Vxi
	{
		DGE_INT3	p;		// Position Vector
		enum { FVF = (DGE_FVF_XYZ), };
	};

	struct VxiD
	{
		DGE_INT3	p;		// Position Vector
		DGE_COLORB	d;		// Diffuse
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_DIFFUSE), };
	};

	struct VxiDUV1
	{
		DGE_INT3	p;		// Position Vector
		DGE_COLORB	d;		// Diffuse
		DGE_INT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_DIFFUSE|DGE_FVF_TEX1), };
	};

	struct VxiN
	{
		DGE_INT3	p;		// Position Vector
		DGE_INT3	n;		// Normal Vector
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL), };
	};

	struct VxiUV1
	{
		DGE_INT3	p;		// Position Vector
		DGE_INT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_TEX1), };
	};

	struct VxiNUV1
	{
		DGE_INT3	p;		// Position Vector
		DGE_INT3	n;		// Normal Vector
		DGE_INT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL|DGE_FVF_TEX1), };
	};

	struct VxiNDUV1
	{
		DGE_INT3	p;		// Position Vector
		DGE_INT3	n;		// Normal Vector
		DGE_COLORB	d;		// Diffuse
		DGE_INT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL|DGE_FVF_DIFFUSE|DGE_FVF_TEX1), };
	};


	////////////////////////////////////////////////////////////////////////////
	// Float type

	struct Vxf
	{
		DGE_FLOAT3	p;		// Position Vector
		enum { FVF = (DGE_FVF_XYZ), };
	};

	struct VxfD
	{
		DGE_FLOAT3	p;		// Position Vector
		DGE_COLORB	d;		// Diffuse
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_DIFFUSE), };
	};

	struct VxfDUV1
	{
		DGE_FLOAT3	p;		// Position Vector
		DGE_COLORB	d;		// Diffuse
		DGE_FLOAT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_DIFFUSE|DGE_FVF_TEX1), };
	};

	struct VxfN
	{
		DGE_FLOAT3	p;		// Position Vector
		DGE_FLOAT3	n;		// Normal Vector
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL), };
	};

	struct VxfUV1
	{
		DGE_FLOAT3	p;		// Position Vector
		DGE_FLOAT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_TEX1), };
	};

	struct VxfNUV1
	{
		DGE_FLOAT3	p;		// Position Vector
		DGE_FLOAT3	n;		// Normal Vector
		DGE_FLOAT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL|DGE_FVF_TEX1), };
	};

	struct VxfNDUV1
	{
		DGE_FLOAT3	p;		// Position Vector
		DGE_FLOAT3	n;		// Normal Vector
		DGE_COLORB	d;		// Diffuse
		DGE_FLOAT2	t;		// Texture Coord
		enum { FVF = (DGE_FVF_XYZ|DGE_FVF_NORMAL|DGE_FVF_DIFFUSE|DGE_FVF_TEX1), };
	};

};


#endif


