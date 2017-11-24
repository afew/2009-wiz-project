#ifndef __gl_h_
#define __gl_h_

/*
** License Applicability. Except to the extent portions of this file are
** made subject to an alternative license as permitted in the SGI Free
** Software License B, Version 1.0 (the "License"), the contents of this
** file are subject only to the provisions of the License. You may not use
** this file except in compliance with the License. You may obtain a copy
** of the License at Silicon Graphics, Inc., attn: Legal Services, 1600
** Amphitheatre Parkway, Mountain View, CA 94043-1351, or at:
** 
** http://oss.sgi.com/projects/FreeB
** 
** Note that, as provided in the License, the Software is distributed on an
** "AS IS" basis, with ALL EXPRESS AND IMPLIED WARRANTIES AND CONDITIONS
** DISCLAIMED, INCLUDING, WITHOUT LIMITATION, ANY IMPLIED WARRANTIES AND
** CONDITIONS OF MERCHANTABILITY, SATISFACTORY QUALITY, FITNESS FOR A
** PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
** 
** Original Code. The Original Code is: OpenGL Sample Implementation,
** Version 1.2.1, released January 26, 2000, developed by Silicon Graphics,
** Inc. The Original Code is Copyright (c) 1991-2000 Silicon Graphics, Inc.
** Copyright in any portions created by third parties is as indicated
** elsewhere herein. All Rights Reserved.
** 
** Additional Notice Provisions: The application programming interfaces
** established by SGI in conjunction with the Original Code are The
** OpenGL(R) Graphics System: A Specification (Version 1.2.1), released
** April 1, 1999; The OpenGL(R) Graphics System Utility Library (Version
** 1.3), released November 4, 1998; and OpenGL(R) Graphics with the X
** Window System(R) (Version 1.3), released October 19, 1998. This software
** was created using the OpenGL(R) version 1.2.1 Sample Implementation
** published by SGI, but has not been independently verified as being
** compliant with the OpenGL(R) version 1.2.1 Specification.
*/

/*------------------------------------------------------------------------
 * 
 * Gerbera OpenGL ES 1.1 API
 * -------------------------
 *
 * (C) 2001-2004 Hybrid Graphics, Ltd.
 * All Rights Reserved.
 *
 * This file consists of source code released by Hybrid 
 * Graphics under the terms of the accompanying End User License 
 * Agreement (EULA). Please do not use this program/source code 
 * before you have read the EULA and have agreed to be bound by 
 * its terms.
 * 
 * Use and/or disclosure outside these terms may result in 
 * irrepairable harm to Hybrid Graphics and legal action against 
 * the party in breach.
 *
 * The most up-to-date version of the OpenGL ES 1.1 specification
 * can be found from http://www.khronos.org/opengles/spec.html
 *
 * $Id: //depot/branches/gerbera/2.0.3/api_opengl/interface/GLES/gl.h#3 $
 * $Date: 2004/09/24 $
 * $Author: jasinb $ *
 *
 *//**
 * \file
 * \brief   Gerbera OpenGL ES interface header.
 * \author  petri@hybrid.fi
 *//*-------------------------------------------------------------------*/

/*-------------------------------------------------------------------------
 * Gerbera version information (use this when reporting bugs)
 *-----------------------------------------------------------------------*/

#define GERBERA_VERSION_MAJOR       2
#define GERBERA_VERSION_MINOR       0
#define GERBERA_VERSION_REVISION    3

/*-------------------------------------------------------------------------
 * Use OpenGL ES 1.1
 * \note If GERBERA_ES_1_1 is defined here, it must also be defined in
 * grApi.h (and vice versa)
 *-----------------------------------------------------------------------*/

#define GERBERA_ES_1_1

/*-------------------------------------------------------------------------
 * Definition of GL_APICALL
 *-----------------------------------------------------------------------*/

/* Define GERBERA_STATIC_LIBRARY for a static library */
#if defined(GERBERA_STATIC_LIBRARY)
#   define GL_APICALL
#else
#   if defined(_WIN32) || defined(__VC32__)             /* Win32 */
#       if defined (GERBERA_DLL_EXPORTS)
#           define GL_APICALL __declspec(dllexport)
#       else
#           define GL_APICALL __declspec(dllimport)
#       endif
#   elif defined (__ARMCC_VERSION)                      /* ADS */
#       define GL_APICALL
#   elif defined (__SYMBIAN32__) && defined (__GCC32__) /* Symbian GCC */
#       define GL_APICALL __declspec(dllexport)
#   elif defined (__GNUC__)                             /* GCC dependencies (kludge) */
#       define GL_APICALL
#   endif
#endif

#if !defined (GL_APICALL)
#   error Unsupported platform! (See GERBERA_STATIC_LIBRARY above)
#endif

/*-------------------------------------------------------------------------
 * Data type definitions
 *-----------------------------------------------------------------------*/

typedef void            GLvoid;
typedef unsigned int    GLenum;
typedef unsigned char   GLboolean;
typedef unsigned int    GLbitfield;
typedef signed char     GLbyte;
typedef short           GLshort;
typedef int             GLint;
typedef int             GLsizei;
typedef unsigned char   GLubyte;
typedef unsigned short  GLushort;
typedef unsigned int    GLuint;
typedef float           GLfloat;
typedef double			GLdouble;
typedef float           GLclampf;
typedef double			GLclampd;
typedef int             GLclampx;
typedef int             GLfixed;


#if defined(GERBERA_ES_1_1)
    typedef long int        GLintptr;
    typedef long int        GLsizeiptr;
#endif /* GERBERA_ES_1_1 */

/*-------------------------------------------------------------------------
 * API enumerations
 *-----------------------------------------------------------------------*/

/* extensions */
#define GL_OES_VERSION_1_0                          1
#define GL_OES_byte_coordinates                     1
#define GL_OES_fixed_point                          1
#define GL_OES_single_precision                     1
#define GL_OES_read_format                          1
#define GL_OES_query_matrix                         1
#define GL_OES_compressed_paletted_texture          1

#if defined(GERBERA_ES_1_1)
#   define GL_OES_VERSION_1_1                           1
#   define GL_OES_matrix_palette                        1
#   define GL_OES_point_sprite                          1
#   define GL_OES_point_size_array                      1
#   define GL_OES_draw_texture                          1
#   define GL_OES_matrix_get                            1

/* EGL extensions */ 
#   define GL_OES_swap_control                          1
#   define GL_OES_render_texture                        1
#endif /* GERBERA_ES_1_1 */

/* boolean values */
#define GL_FALSE                                    0
#define GL_TRUE                                     1

/* common values */
#define GL_ZERO                                     0
#define GL_ONE                                      1

/* comparison functions */
#define GL_NEVER                                    0x0200
#define GL_LESS                                     0x0201
#define GL_EQUAL                                    0x0202
#define GL_LEQUAL                                   0x0203
#define GL_GREATER                                  0x0204
#define GL_NOTEQUAL                                 0x0205
#define GL_GEQUAL                                   0x0206
#define GL_ALWAYS                                   0x0207

/* data types */
#define GL_BYTE                                     0x1400
#define GL_UNSIGNED_BYTE                            0x1401
#define GL_SHORT                                    0x1402
#define GL_UNSIGNED_SHORT                           0x1403
#define GL_FLOAT                                    0x1406
#define GL_FIXED                                    0x140C

/* primitives */
#define GL_POINTS                                   0x0000
#define GL_LINES                                    0x0001
#define GL_LINE_LOOP                                0x0002
#define GL_LINE_STRIP                               0x0003
#define GL_TRIANGLES                                0x0004
#define GL_TRIANGLE_STRIP                           0x0005
#define GL_TRIANGLE_FAN                             0x0006

/* vertex arrays */
#define GL_VERTEX_ARRAY                             0x8074
#define GL_NORMAL_ARRAY                             0x8075
#define GL_COLOR_ARRAY                              0x8076
#define GL_TEXTURE_COORD_ARRAY                      0x8078
#if defined(GERBERA_ES_1_1)
#   define GL_MATRIX_INDEX_ARRAY_OES                0x8844
#   define GL_WEIGHT_ARRAY_OES                      0x86AD
#   define GL_POINT_SIZE_ARRAY_OES                  0x8B9C
#endif /* GERBERA_ES_1_1 */

#if defined(GERBERA_ES_1_1)
    /* vertex buffer objects */
#   define GL_ARRAY_BUFFER                          0x8892
#   define GL_ELEMENT_ARRAY_BUFFER                  0x8893
#   define GL_STREAM_DRAW                           0x88E0
#   define GL_STATIC_DRAW                           0x88E4
#   define GL_DYNAMIC_DRAW                          0x88E8
#   define GL_BUFFER_SIZE                           0x8764
#   define GL_BUFFER_USAGE                          0x8765
#   define GL_BUFFER_ACCESS                         0x88BB
#   define GL_WRITE_ONLY                            0x88B9
#endif /* GERBERA_ES_1_1 */

/* matrix mode */
#define GL_MODELVIEW                                0x1700
#define GL_PROJECTION                               0x1701
#define GL_TEXTURE                                  0x1702

#if defined(GERBERA_ES_1_1)
#   define GL_MATRIX_PALETTE_OES                    0x8840
#endif /* GERBERA_ES_1_1 */

/* smoothing */
#define GL_POINT_SMOOTH                             0x0B10
#define GL_LINE_SMOOTH                              0x0B20

/* geometry */
#define GL_CW                                       0x0900
#define GL_CCW                                      0x0901
#define GL_FRONT                                    0x0404
#define GL_BACK                                     0x0405
#define GL_CULL_FACE                                0x0B44
#define GL_POLYGON_OFFSET_FILL                      0x8037

/* lighting */
#define GL_LIGHTING                                 0x0B50
#define GL_LIGHT0                                   0x4000
#define GL_LIGHT1                                   0x4001
#define GL_LIGHT2                                   0x4002
#define GL_LIGHT3                                   0x4003
#define GL_LIGHT4                                   0x4004
#define GL_LIGHT5                                   0x4005
#define GL_LIGHT6                                   0x4006
#define GL_LIGHT7                                   0x4007
#define GL_SPOT_EXPONENT                            0x1205
#define GL_SPOT_CUTOFF                              0x1206
#define GL_CONSTANT_ATTENUATION                     0x1207
#define GL_LINEAR_ATTENUATION                       0x1208
#define GL_QUADRATIC_ATTENUATION                    0x1209
#define GL_AMBIENT                                  0x1200
#define GL_DIFFUSE                                  0x1201
#define GL_SPECULAR                                 0x1202
#define GL_EMISSION                                 0x1600
#define GL_SHININESS                                0x1601
#define GL_POSITION                                 0x1203
#define GL_SPOT_DIRECTION                           0x1204
#define GL_AMBIENT_AND_DIFFUSE                      0x1602
#define GL_LIGHT_MODEL_TWO_SIDE                     0x0B52
#define GL_LIGHT_MODEL_AMBIENT                      0x0B53
#define GL_FRONT_AND_BACK                           0x0408
#define GL_FLAT                                     0x1D00
#define GL_SMOOTH                                   0x1D01
#define GL_COLOR_MATERIAL                           0x0B57
#define GL_NORMALIZE                                0x0BA1

/* blending */
#define GL_ADD                                      0x0104
#define GL_BLEND                                    0x0BE2
#define GL_SRC_COLOR                                0x0300
#define GL_ONE_MINUS_SRC_COLOR                      0x0301
#define GL_SRC_ALPHA                                0x0302
#define GL_ONE_MINUS_SRC_ALPHA                      0x0303
#define GL_DST_ALPHA                                0x0304
#define GL_ONE_MINUS_DST_ALPHA                      0x0305
#define GL_DST_COLOR                                0x0306
#define GL_ONE_MINUS_DST_COLOR                      0x0307
#define GL_SRC_ALPHA_SATURATE                       0x0308

/* fog */
#define GL_FOG                                      0x0B60
#define GL_FOG_DENSITY                              0x0B62
#define GL_FOG_START                                0x0B63
#define GL_FOG_END                                  0x0B64
#define GL_FOG_MODE                                 0x0B65
#define GL_FOG_COLOR                                0x0B66
#define GL_EXP                                      0x0800
#define GL_EXP2                                     0x0801

/* logic ops */
#define GL_CLEAR                                    0x1500
#define GL_AND                                      0x1501
#define GL_AND_REVERSE                              0x1502
#define GL_COPY                                     0x1503
#define GL_AND_INVERTED                             0x1504
#define GL_NOOP                                     0x1505
#define GL_XOR                                      0x1506
#define GL_OR                                       0x1507
#define GL_NOR                                      0x1508
#define GL_EQUIV                                    0x1509
#define GL_INVERT                                   0x150A
#define GL_OR_REVERSE                               0x150B
#define GL_COPY_INVERTED                            0x150C
#define GL_OR_INVERTED                              0x150D
#define GL_NAND                                     0x150E
#define GL_SET                                      0x150F

/* capabilities */
#define GL_DEPTH_TEST                               0x0B71
#define GL_STENCIL_TEST                             0x0B90
#define GL_ALPHA_TEST                               0x0BC0
#define GL_DITHER                                   0x0BD0
#define GL_COLOR_LOGIC_OP                           0x0BF2
#define GL_SCISSOR_TEST                             0x0C11
#define GL_RESCALE_NORMAL                           0x803A

#if defined(GERBERA_ES_1_1)
#   define GL_POINT_SPRITE_OES                      0x8861
#endif /* GERBERA_ES_1_1 */

/* stencil ops */
#define GL_KEEP                                     0x1E00
#define GL_REPLACE                                  0x1E01
#define GL_INCR                                     0x1E02
#define GL_DECR                                     0x1E03

/* buffers, pixel reading */
#define GL_ALPHA                                    0x1906
#define GL_RGB                                      0x1907
#define GL_RGBA                                     0x1908
#define GL_LUMINANCE                                0x1909
#define GL_LUMINANCE_ALPHA                          0x190A

/* getters */
#define GL_SMOOTH_POINT_SIZE_RANGE                  0x0B12
#define GL_SMOOTH_LINE_WIDTH_RANGE                  0x0B22
#define GL_ALIASED_POINT_SIZE_RANGE                 0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE                 0x846E
#define GL_MAX_LIGHTS                               0x0D31
#define GL_MAX_TEXTURE_SIZE                         0x0D33
#define GL_MAX_MODELVIEW_STACK_DEPTH                0x0D36
#define GL_MAX_PROJECTION_STACK_DEPTH               0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH                  0x0D39
#define GL_MAX_VIEWPORT_DIMS                        0x0D3A
#define GL_SUBPIXEL_BITS                            0x0D50
#define GL_RED_BITS                                 0x0D52
#define GL_GREEN_BITS                               0x0D53
#define GL_BLUE_BITS                                0x0D54
#define GL_ALPHA_BITS                               0x0D55
#define GL_DEPTH_BITS                               0x0D56
#define GL_STENCIL_BITS                             0x0D57
#define GL_MAX_ELEMENTS_VERTICES                    0x80E8
#define GL_MAX_ELEMENTS_INDICES                     0x80E9
#define GL_MAX_TEXTURE_UNITS                        0x84E2
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS           0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS               0x86A3
#define GL_IMPLEMENTATION_COLOR_READ_TYPE_OES       0x8B9A
#define GL_IMPLEMENTATION_COLOR_READ_FORMAT_OES     0x8B9B

#if defined(GERBERA_ES_1_1)
#   define GL_MAX_PALETTE_MATRICES_OES              0x8842
#   define GL_MAX_VERTEX_UNITS_OES                  0x86A4
#   define GL_MAX_CLIP_PLANES                       0x0D32

/* dynamic gets */
#   define GL_CLIENT_ACTIVE_TEXTURE                 0x84E1
#   define GL_VERTEX_ARRAY_SIZE                     0x807A
#   define GL_VERTEX_ARRAY_TYPE                     0x807B
#   define GL_VERTEX_ARRAY_POINTER                  0x808E
#   define GL_VERTEX_ARRAY_STRIDE                   0x807C
#   define GL_NORMAL_ARRAY_TYPE                     0x807E
#   define GL_NORMAL_ARRAY_STRIDE                   0x807F
#   define GL_NORMAL_ARRAY_POINTER                  0x808F
#   define GL_COLOR_ARRAY_SIZE                      0x8081
#   define GL_COLOR_ARRAY_TYPE                      0x8082
#   define GL_COLOR_ARRAY_STRIDE                    0x8083
#   define GL_COLOR_ARRAY_POINTER                   0x8090
#   define GL_TEXTURE_COORD_ARRAY_SIZE              0x8088
#   define GL_TEXTURE_COORD_ARRAY_TYPE              0x8089
#   define GL_TEXTURE_COORD_ARRAY_STRIDE            0x808A
#   define GL_TEXTURE_COORD_ARRAY_POINTER           0x8092
#   define GL_ARRAY_BUFFER_BINDING                  0x8894
#   define GL_VERTEX_ARRAY_BUFFER_BINDING           0x8896
#   define GL_NORMAL_ARRAY_BUFFER_BINDING           0x8897
#   define GL_COLOR_ARRAY_BUFFER_BINDING            0x8898
#   define GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING    0x889A
#   define GL_ELEMENT_ARRAY_BUFFER_BINDING          0x8895
#   define GL_VIEWPORT                              0x0BA2
#   define GL_DEPTH_RANGE                           0x0B70
#   define GL_MATRIX_MODE                           0x0BA0
#   define GL_SHADE_MODEL                           0x0B54
#   define GL_POINT_SIZE                            0x0B11
#   define GL_LINE_WIDTH                            0x0B21
#   define GL_CULL_FACE_MODE                        0x0B45
#   define GL_FRONT_FACE                            0x0B46
#   define GL_POLYGON_OFFSET_FACTOR                 0x8038
#   define GL_POLYGON_OFFSET_UNITS                  0x2A00
#   define GL_TEXTURE_BINDING_2D                    0x8069
#   define GL_ACTIVE_TEXTURE                        0x84E0
#   define GL_SCISSOR_BOX                           0x0C10
#   define GL_ALPHA_TEST_FUNC                       0x0BC1
#   define GL_ALPHA_TEST_REF                        0x0BC2
#   define GL_STENCIL_FUNC                          0x0B92
#   define GL_STENCIL_VALUE_MASK                    0x0B93
#   define GL_STENCIL_REF                           0x0B97
#   define GL_STENCIL_FAIL                          0x0B94
#   define GL_STENCIL_PASS_DEPTH_FAIL               0x0B95
#   define GL_STENCIL_PASS_DEPTH_PASS               0x0B96
#   define GL_DEPTH_FUNC                            0x0B74
#   define GL_BLEND_SRC                             0x0BE1
#   define GL_BLEND_DST                             0x0BE0
#   define GL_LOGIC_OP_MODE                         0x0BF0
#   define GL_COLOR_WRITEMASK                       0x0C23
#   define GL_DEPTH_WRITEMASK                       0x0B72
#   define GL_STENCIL_WRITEMASK                     0x0B98
#   define GL_COLOR_CLEAR_VALUE                     0x0C22
#   define GL_DEPTH_CLEAR_VALUE                     0x0B73
#   define GL_STENCIL_CLEAR_VALUE                   0x0B91
#   define GL_MODELVIEW_MATRIX                      0x0BA6
#   define GL_PROJECTION_MATRIX                     0x0BA7
#   define GL_TEXTURE_MATRIX                        0x0BA8
#   define GL_MODELVIEW_STACK_DEPTH                 0x0BA3
#   define GL_PROJECTION_STACK_DEPTH                0x0BA4
#   define GL_TEXTURE_STACK_DEPTH                   0x0BA5
#   define GL_MATRIX_INDEX_ARRAY_SIZE_OES           0x8846
#   define GL_MATRIX_INDEX_ARRAY_TYPE_OES           0x8847
#   define GL_MATRIX_INDEX_ARRAY_STRIDE_OES         0x8848
#   define GL_MATRIX_INDEX_ARRAY_POINTER_OES        0x8849
#   define GL_MATRIX_INDEX_ARRAY_BUFFER_BINDING_OES 0x8B9E
#   define GL_WEIGHT_ARRAY_SIZE_OES                 0x86AB
#   define GL_WEIGHT_ARRAY_TYPE_OES                 0x86A9
#   define GL_WEIGHT_ARRAY_STRIDE_OES               0x86AA
#   define GL_WEIGHT_ARRAY_POINTER_OES              0x86AC
#   define GL_WEIGHT_ARRAY_BUFFER_BINDING_OES       0x889E
#   define GL_POINT_SIZE_ARRAY_TYPE_OES             0x898A
#   define GL_POINT_SIZE_ARRAY_STRIDE_OES           0x898B
#   define GL_POINT_SIZE_ARRAY_POINTER_OES          0x898C
#   define GL_POINT_SIZE_ARRAY_BUFFER_BINDING_OES   0x8B9F
#   define GL_SAMPLE_COVERAGE_INVERT                0x80AB
#   define GL_SAMPLE_COVERAGE_VALUE                 0x80AA
#   define GL_POINT_SIZE_MIN                        0x8126
#   define GL_POINT_SIZE_MAX                        0x8127
#   define GL_POINT_FADE_THRESHOLD_SIZE             0x8128
#   define GL_POINT_DISTANCE_ATTENUATION            0x8129
#   define GL_CURRENT_COLOR                         0x0B00
#   define GL_CURRENT_NORMAL                        0x0B02
#   define GL_CURRENT_TEXTURE_COORDS                0x0B03
#   define GL_MODELVIEW_MATRIX_FLOAT_AS_INT_BITS_OES    0x898D
#   define GL_PROJECTION_MATRIX_FLOAT_AS_INT_BITS_OES   0x898E
#   define GL_TEXTURE_MATRIX_FLOAT_AS_INT_BITS_OES      0x898F
#endif /* GERBERA_ES_1_1 */

/* clip planes */
#if defined(GERBERA_ES_1_1)
#   define GL_CLIP_PLANE0                           0x3000
#   define GL_CLIP_PLANE1                           0x3001
#   define GL_CLIP_PLANE2                           0x3002
#   define GL_CLIP_PLANE3                           0x3003
#   define GL_CLIP_PLANE4                           0x3004
#   define GL_CLIP_PLANE5                           0x3005
#endif /* GERBERA_ES_1_1 */

/* hints */
#define GL_PERSPECTIVE_CORRECTION_HINT              0x0C50
#define GL_LINE_SMOOTH_HINT                         0x0C52
#define GL_POINT_SMOOTH_HINT                        0x0C51
#define GL_FOG_HINT                                 0x0C54
#define GL_DONT_CARE                                0x1100
#define GL_FASTEST                                  0x1101
#define GL_NICEST                                   0x1102

#if defined(GERBERA_ES_1_1)
#   define GL_GENERATE_MIPMAP_HINT                  0x8192
#endif /* GERBERA_ES_1_1 */

/* pixel store */
#define GL_UNPACK_ALIGNMENT                         0x0CF5
#define GL_PACK_ALIGNMENT                           0x0D05

/* multisample */
#define GL_MULTISAMPLE                              0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE                 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE                      0x809F
#define GL_SAMPLE_COVERAGE                          0x80A0
#define GL_SAMPLE_BUFFERS                           0x80A8
#define GL_SAMPLES                                  0x80A9

/* texture mapping */
#define GL_TEXTURE_2D                               0x0DE1
#define GL_TEXTURE_ENV                              0x2300
#define GL_TEXTURE_ENV_MODE                         0x2200
#define GL_TEXTURE_MAG_FILTER                       0x2800
#define GL_TEXTURE_MIN_FILTER                       0x2801
#define GL_TEXTURE_WRAP_S                           0x2802
#define GL_TEXTURE_WRAP_T                           0x2803
#define GL_TEXTURE_ENV_COLOR                        0x2201
#define GL_MODULATE                                 0x2100
#define GL_DECAL                                    0x2101
#define GL_NEAREST                                  0x2600
#define GL_LINEAR                                   0x2601
#define GL_NEAREST_MIPMAP_NEAREST                   0x2700
#define GL_LINEAR_MIPMAP_NEAREST                    0x2701
#define GL_NEAREST_MIPMAP_LINEAR                    0x2702
#define GL_LINEAR_MIPMAP_LINEAR                     0x2703
#define GL_REPEAT                                   0x2901
#define GL_CLAMP_TO_EDGE                            0x812F

#if defined(GERBERA_ES_1_1)
#   define GL_GENERATE_MIPMAP                       0x8191
#   define GL_COORD_REPLACE_OES                     0x8862
#   define GL_TEXTURE_CROP_RECT_OES                 0x8B9D
#endif /* GERBERA_ES_1_1 */

/* tex env combine */
#if defined(GERBERA_ES_1_1)
#   define GL_COMBINE                               0x8570
#   define GL_COMBINE_RGB                           0x8571
#   define GL_COMBINE_ALPHA                         0x8572
#   define GL_SOURCE0_RGB                           0x8580
#   define GL_SOURCE1_RGB                           0x8581
#   define GL_SOURCE2_RGB                           0x8582
#   define GL_SOURCE0_ALPHA                         0x8588
#   define GL_SOURCE1_ALPHA                         0x8589
#   define GL_SOURCE2_ALPHA                         0x858A
#   define GL_SRC0_RGB                              GL_SOURCE0_RGB      
#   define GL_SRC1_RGB                              GL_SOURCE1_RGB      
#   define GL_SRC2_RGB                              GL_SOURCE2_RGB      
#   define GL_SRC0_ALPHA                            GL_SOURCE0_ALPHA        
#   define GL_SRC1_ALPHA                            GL_SOURCE1_ALPHA        
#   define GL_SRC2_ALPHA                            GL_SOURCE2_ALPHA        
#   define GL_OPERAND0_RGB                          0x8590
#   define GL_OPERAND1_RGB                          0x8591
#   define GL_OPERAND2_RGB                          0x8592
#   define GL_OPERAND0_ALPHA                        0x8598
#   define GL_OPERAND1_ALPHA                        0x8599
#   define GL_OPERAND2_ALPHA                        0x859A
#   define GL_RGB_SCALE                             0x8573
#   define GL_ALPHA_SCALE                           0x0D1C
#   define GL_ADD_SIGNED                            0x8574
#   define GL_INTERPOLATE                           0x8575
#   define GL_SUBTRACT                              0x84E7
#   define GL_DOT3_RGB                              0x86AE
#   define GL_DOT3_RGBA                             0x86AF
#   define GL_CONSTANT                              0x8576
#   define GL_PRIMARY_COLOR                         0x8577
#   define GL_PREVIOUS                              0x8578
#endif /* GERBERA_ES_1_1 */

/* paletted internal formats */
#define GL_PALETTE4_RGB8_OES                        0x8B90
#define GL_PALETTE4_RGBA8_OES                       0x8B91
#define GL_PALETTE4_R5_G6_B5_OES                    0x8B92
#define GL_PALETTE4_RGBA4_OES                       0x8B93
#define GL_PALETTE4_RGB5_A1_OES                     0x8B94
#define GL_PALETTE8_RGB8_OES                        0x8B95
#define GL_PALETTE8_RGBA8_OES                       0x8B96
#define GL_PALETTE8_R5_G6_B5_OES                    0x8B97
#define GL_PALETTE8_RGBA4_OES                       0x8B98
#define GL_PALETTE8_RGB5_A1_OES                     0x8B99

/* utility */
#define GL_VENDOR                                   0x1F00
#define GL_RENDERER                                 0x1F01
#define GL_VERSION                                  0x1F02
#define GL_EXTENSIONS                               0x1F03

/* errors */
#define GL_NO_ERROR                                 0
#define GL_INVALID_ENUM                             0x0500
#define GL_INVALID_VALUE                            0x0501
#define GL_INVALID_OPERATION                        0x0502
#define GL_STACK_OVERFLOW                           0x0503
#define GL_STACK_UNDERFLOW                          0x0504
#define GL_OUT_OF_MEMORY                            0x0505

/* texture formats */
#define GL_UNSIGNED_SHORT_5_6_5                     0x8363
#define GL_UNSIGNED_SHORT_4_4_4_4                   0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1                   0x8034

/* buffer bits */
#define GL_DEPTH_BUFFER_BIT                         0x00000100
#define GL_STENCIL_BUFFER_BIT                       0x00000400
#define GL_COLOR_BUFFER_BIT                         0x00004000

/* ARB_multitexture */
#define GL_TEXTURE0                                 0x84C0
#define GL_TEXTURE1                                 0x84C1
#define GL_TEXTURE2                                 0x84C2
#define GL_TEXTURE3                                 0x84C3
#define GL_TEXTURE4                                 0x84C4
#define GL_TEXTURE5                                 0x84C5
#define GL_TEXTURE6                                 0x84C6
#define GL_TEXTURE7                                 0x84C7
#define GL_TEXTURE8                                 0x84C8
#define GL_TEXTURE9                                 0x84C9
#define GL_TEXTURE10                                0x84CA
#define GL_TEXTURE11                                0x84CB
#define GL_TEXTURE12                                0x84CC
#define GL_TEXTURE13                                0x84CD
#define GL_TEXTURE14                                0x84CE
#define GL_TEXTURE15                                0x84CF
#define GL_TEXTURE16                                0x84D0
#define GL_TEXTURE17                                0x84D1
#define GL_TEXTURE18                                0x84D2
#define GL_TEXTURE19                                0x84D3
#define GL_TEXTURE20                                0x84D4
#define GL_TEXTURE21                                0x84D5
#define GL_TEXTURE22                                0x84D6
#define GL_TEXTURE23                                0x84D7
#define GL_TEXTURE24                                0x84D8
#define GL_TEXTURE25                                0x84D9
#define GL_TEXTURE26                                0x84DA
#define GL_TEXTURE27                                0x84DB
#define GL_TEXTURE28                                0x84DC
#define GL_TEXTURE29                                0x84DD
#define GL_TEXTURE30                                0x84DE
#define GL_TEXTURE31                                0x84DF

/*-------------------------------------------------------------------------
 * Function prototypes
 *-----------------------------------------------------------------------*/

#if defined (__cplusplus)
extern "C" {
#endif


#if defined(_WIN32) || defined(_WIN32)

	#ifndef WINGDIAPI
	#define WINGDIAPI __declspec(dllimport)
	#endif

	#ifndef APIENTRY
	#define APIENTRY  __stdcall
	#endif

	#ifndef DGEAPI
	#define DGEAPI extern
	#endif

	WINGDIAPI void APIENTRY glAccum (GLenum op, GLfloat value);
	WINGDIAPI void APIENTRY glAlphaFunc (GLenum func, GLclampf ref);
	WINGDIAPI GLboolean APIENTRY glAreTexturesResident (GLsizei n, const GLuint *textures, GLboolean *residences);
	WINGDIAPI void APIENTRY glArrayElement (GLint i);
	WINGDIAPI void APIENTRY glBegin (GLenum mode);
	WINGDIAPI void APIENTRY glBindTexture (GLenum target, GLuint texture);
	WINGDIAPI void APIENTRY glBitmap (GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap);
	WINGDIAPI void APIENTRY glBlendFunc (GLenum sfactor, GLenum dfactor);
	WINGDIAPI void APIENTRY glCallList (GLuint list);
	WINGDIAPI void APIENTRY glCallLists (GLsizei n, GLenum type, const GLvoid *lists);
	WINGDIAPI void APIENTRY glClear (GLbitfield mask);
	WINGDIAPI void APIENTRY glClearAccum (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	WINGDIAPI void APIENTRY glClearColor (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	WINGDIAPI void APIENTRY glClearDepth (GLclampd depth);
	WINGDIAPI void APIENTRY glClearIndex (GLfloat c);
	WINGDIAPI void APIENTRY glClearStencil (GLint s);
	WINGDIAPI void APIENTRY glClipPlane (GLenum plane, const GLdouble *equation);
	WINGDIAPI void APIENTRY glColor3b (GLbyte red, GLbyte green, GLbyte blue);
	WINGDIAPI void APIENTRY glColor3bv (const GLbyte *v);
	WINGDIAPI void APIENTRY glColor3d (GLdouble red, GLdouble green, GLdouble blue);
	WINGDIAPI void APIENTRY glColor3dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glColor3f (GLfloat red, GLfloat green, GLfloat blue);
	WINGDIAPI void APIENTRY glColor3fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glColor3i (GLint red, GLint green, GLint blue);
	WINGDIAPI void APIENTRY glColor3iv (const GLint *v);
	WINGDIAPI void APIENTRY glColor3s (GLshort red, GLshort green, GLshort blue);
	WINGDIAPI void APIENTRY glColor3sv (const GLshort *v);
	WINGDIAPI void APIENTRY glColor3ub (GLubyte red, GLubyte green, GLubyte blue);
	WINGDIAPI void APIENTRY glColor3ubv (const GLubyte *v);
	WINGDIAPI void APIENTRY glColor3ui (GLuint red, GLuint green, GLuint blue);
	WINGDIAPI void APIENTRY glColor3uiv (const GLuint *v);
	WINGDIAPI void APIENTRY glColor3us (GLushort red, GLushort green, GLushort blue);
	WINGDIAPI void APIENTRY glColor3usv (const GLushort *v);
	WINGDIAPI void APIENTRY glColor4b (GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha);
	WINGDIAPI void APIENTRY glColor4bv (const GLbyte *v);
	WINGDIAPI void APIENTRY glColor4d (GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha);
	WINGDIAPI void APIENTRY glColor4dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glColor4f (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	WINGDIAPI void APIENTRY glColor4fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glColor4i (GLint red, GLint green, GLint blue, GLint alpha);
	WINGDIAPI void APIENTRY glColor4iv (const GLint *v);
	WINGDIAPI void APIENTRY glColor4s (GLshort red, GLshort green, GLshort blue, GLshort alpha);
	WINGDIAPI void APIENTRY glColor4sv (const GLshort *v);
	WINGDIAPI void APIENTRY glColor4ub (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
	WINGDIAPI void APIENTRY glColor4ubv (const GLubyte *v);
	WINGDIAPI void APIENTRY glColor4ui (GLuint red, GLuint green, GLuint blue, GLuint alpha);
	WINGDIAPI void APIENTRY glColor4uiv (const GLuint *v);
	WINGDIAPI void APIENTRY glColor4us (GLushort red, GLushort green, GLushort blue, GLushort alpha);
	WINGDIAPI void APIENTRY glColor4usv (const GLushort *v);
	WINGDIAPI void APIENTRY glColorMask (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	WINGDIAPI void APIENTRY glColorMaterial (GLenum face, GLenum mode);
	WINGDIAPI void APIENTRY glColorPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glCopyPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum type);
	WINGDIAPI void APIENTRY glCopyTexImage1D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLint border);
	WINGDIAPI void APIENTRY glCopyTexImage2D (GLenum target, GLint level, GLenum internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	WINGDIAPI void APIENTRY glCopyTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width);
	WINGDIAPI void APIENTRY glCopyTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	WINGDIAPI void APIENTRY glCullFace (GLenum mode);
	WINGDIAPI void APIENTRY glDeleteLists (GLuint list, GLsizei range);
	WINGDIAPI void APIENTRY glDeleteTextures (GLsizei n, const GLuint *textures);
	WINGDIAPI void APIENTRY glDepthFunc (GLenum func);
	WINGDIAPI void APIENTRY glDepthMask (GLboolean flag);
	WINGDIAPI void APIENTRY glDepthRange (GLclampd zNear, GLclampd zFar);
	WINGDIAPI void APIENTRY glDisable (GLenum cap);
	WINGDIAPI void APIENTRY glDisableClientState (GLenum array);
	WINGDIAPI void APIENTRY glDrawArrays (GLenum mode, GLint first, GLsizei count);
	WINGDIAPI void APIENTRY glDrawBuffer (GLenum mode);
	WINGDIAPI void APIENTRY glDrawElements (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);
	WINGDIAPI void APIENTRY glDrawPixels (GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glEdgeFlag (GLboolean flag);
	WINGDIAPI void APIENTRY glEdgeFlagPointer (GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glEdgeFlagv (const GLboolean *flag);
	WINGDIAPI void APIENTRY glEnable (GLenum cap);
	WINGDIAPI void APIENTRY glEnableClientState (GLenum array);
	WINGDIAPI void APIENTRY glEnd (void);
	WINGDIAPI void APIENTRY glEndList (void);
	WINGDIAPI void APIENTRY glEvalCoord1d (GLdouble u);
	WINGDIAPI void APIENTRY glEvalCoord1dv (const GLdouble *u);
	WINGDIAPI void APIENTRY glEvalCoord1f (GLfloat u);
	WINGDIAPI void APIENTRY glEvalCoord1fv (const GLfloat *u);
	WINGDIAPI void APIENTRY glEvalCoord2d (GLdouble u, GLdouble v);
	WINGDIAPI void APIENTRY glEvalCoord2dv (const GLdouble *u);
	WINGDIAPI void APIENTRY glEvalCoord2f (GLfloat u, GLfloat v);
	WINGDIAPI void APIENTRY glEvalCoord2fv (const GLfloat *u);
	WINGDIAPI void APIENTRY glEvalMesh1 (GLenum mode, GLint i1, GLint i2);
	WINGDIAPI void APIENTRY glEvalMesh2 (GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2);
	WINGDIAPI void APIENTRY glEvalPoint1 (GLint i);
	WINGDIAPI void APIENTRY glEvalPoint2 (GLint i, GLint j);
	WINGDIAPI void APIENTRY glFeedbackBuffer (GLsizei size, GLenum type, GLfloat *buffer);
	WINGDIAPI void APIENTRY glFinish (void);
	WINGDIAPI void APIENTRY glFlush (void);
	WINGDIAPI void APIENTRY glFogf (GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glFogfv (GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glFogi (GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glFogiv (GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glFrontFace (GLenum mode);
	WINGDIAPI void APIENTRY glFrustum (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	WINGDIAPI GLuint APIENTRY glGenLists (GLsizei range);
	WINGDIAPI void APIENTRY glGenTextures (GLsizei n, GLuint *textures);
	WINGDIAPI void APIENTRY glGetBooleanv (GLenum pname, GLboolean *params);
	WINGDIAPI void APIENTRY glGetClipPlane (GLenum plane, GLdouble *equation);
	WINGDIAPI void APIENTRY glGetDoublev (GLenum pname, GLdouble *params);
	WINGDIAPI GLenum APIENTRY glGetError (void);
	WINGDIAPI void APIENTRY glGetFloatv (GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetIntegerv (GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetLightfv (GLenum light, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetLightiv (GLenum light, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetMapdv (GLenum target, GLenum query, GLdouble *v);
	WINGDIAPI void APIENTRY glGetMapfv (GLenum target, GLenum query, GLfloat *v);
	WINGDIAPI void APIENTRY glGetMapiv (GLenum target, GLenum query, GLint *v);
	WINGDIAPI void APIENTRY glGetMaterialfv (GLenum face, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetMaterialiv (GLenum face, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetPixelMapfv (GLenum map, GLfloat *values);
	WINGDIAPI void APIENTRY glGetPixelMapuiv (GLenum map, GLuint *values);
	WINGDIAPI void APIENTRY glGetPixelMapusv (GLenum map, GLushort *values);
	WINGDIAPI void APIENTRY glGetPointerv (GLenum pname, GLvoid* *params);
	WINGDIAPI void APIENTRY glGetPolygonStipple (GLubyte *mask);
	WINGDIAPI const GLubyte * APIENTRY glGetString (GLenum name);
	WINGDIAPI void APIENTRY glGetTexEnvfv (GLenum target, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexEnviv (GLenum target, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetTexGendv (GLenum coord, GLenum pname, GLdouble *params);
	WINGDIAPI void APIENTRY glGetTexGenfv (GLenum coord, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexGeniv (GLenum coord, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetTexImage (GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels);
	WINGDIAPI void APIENTRY glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glGetTexParameterfv (GLenum target, GLenum pname, GLfloat *params);
	WINGDIAPI void APIENTRY glGetTexParameteriv (GLenum target, GLenum pname, GLint *params);
	WINGDIAPI void APIENTRY glHint (GLenum target, GLenum mode);
	WINGDIAPI void APIENTRY glIndexMask (GLuint mask);
	WINGDIAPI void APIENTRY glIndexPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glIndexd (GLdouble c);
	WINGDIAPI void APIENTRY glIndexdv (const GLdouble *c);
	WINGDIAPI void APIENTRY glIndexf (GLfloat c);
	WINGDIAPI void APIENTRY glIndexfv (const GLfloat *c);
	WINGDIAPI void APIENTRY glIndexi (GLint c);
	WINGDIAPI void APIENTRY glIndexiv (const GLint *c);
	WINGDIAPI void APIENTRY glIndexs (GLshort c);
	WINGDIAPI void APIENTRY glIndexsv (const GLshort *c);
	WINGDIAPI void APIENTRY glIndexub (GLubyte c);
	WINGDIAPI void APIENTRY glIndexubv (const GLubyte *c);
	WINGDIAPI void APIENTRY glInitNames (void);
	WINGDIAPI void APIENTRY glInterleavedArrays (GLenum format, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI GLboolean APIENTRY glIsEnabled (GLenum cap);
	WINGDIAPI GLboolean APIENTRY glIsList (GLuint list);
	WINGDIAPI GLboolean APIENTRY glIsTexture (GLuint texture);
	WINGDIAPI void APIENTRY glLightModelf (GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glLightModelfv (GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glLightModeli (GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glLightModeliv (GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glLightf (GLenum light, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glLightfv (GLenum light, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glLighti (GLenum light, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glLightiv (GLenum light, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glLineStipple (GLint factor, GLushort pattern);
	WINGDIAPI void APIENTRY glLineWidth (GLfloat width);
	WINGDIAPI void APIENTRY glListBase (GLuint base);
	WINGDIAPI void APIENTRY glLoadIdentity (void);
	WINGDIAPI void APIENTRY glLoadMatrixd (const GLdouble *m);
	WINGDIAPI void APIENTRY glLoadMatrixf (const GLfloat *m);
	WINGDIAPI void APIENTRY glLoadName (GLuint name);
	WINGDIAPI void APIENTRY glLogicOp (GLenum opcode);
	WINGDIAPI void APIENTRY glMap1d (GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points);
	WINGDIAPI void APIENTRY glMap1f (GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points);
	WINGDIAPI void APIENTRY glMap2d (GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points);
	WINGDIAPI void APIENTRY glMap2f (GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points);
	WINGDIAPI void APIENTRY glMapGrid1d (GLint un, GLdouble u1, GLdouble u2);
	WINGDIAPI void APIENTRY glMapGrid1f (GLint un, GLfloat u1, GLfloat u2);
	WINGDIAPI void APIENTRY glMapGrid2d (GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2);
	WINGDIAPI void APIENTRY glMapGrid2f (GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2);
	WINGDIAPI void APIENTRY glMaterialf (GLenum face, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glMaterialfv (GLenum face, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glMateriali (GLenum face, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glMaterialiv (GLenum face, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glMatrixMode (GLenum mode);
	WINGDIAPI void APIENTRY glMultMatrixd (const GLdouble *m);
	WINGDIAPI void APIENTRY glMultMatrixf (const GLfloat *m);
	WINGDIAPI void APIENTRY glNewList (GLuint list, GLenum mode);
	WINGDIAPI void APIENTRY glNormal3b (GLbyte nx, GLbyte ny, GLbyte nz);
	WINGDIAPI void APIENTRY glNormal3bv (const GLbyte *v);
	WINGDIAPI void APIENTRY glNormal3d (GLdouble nx, GLdouble ny, GLdouble nz);
	WINGDIAPI void APIENTRY glNormal3dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glNormal3f (GLfloat nx, GLfloat ny, GLfloat nz);
	WINGDIAPI void APIENTRY glNormal3fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glNormal3i (GLint nx, GLint ny, GLint nz);
	WINGDIAPI void APIENTRY glNormal3iv (const GLint *v);
	WINGDIAPI void APIENTRY glNormal3s (GLshort nx, GLshort ny, GLshort nz);
	WINGDIAPI void APIENTRY glNormal3sv (const GLshort *v);
	WINGDIAPI void APIENTRY glNormalPointer (GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glOrtho (GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	WINGDIAPI void APIENTRY glPassThrough (GLfloat token);
	WINGDIAPI void APIENTRY glPixelMapfv (GLenum map, GLsizei mapsize, const GLfloat *values);
	WINGDIAPI void APIENTRY glPixelMapuiv (GLenum map, GLsizei mapsize, const GLuint *values);
	WINGDIAPI void APIENTRY glPixelMapusv (GLenum map, GLsizei mapsize, const GLushort *values);
	WINGDIAPI void APIENTRY glPixelStoref (GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glPixelStorei (GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glPixelTransferf (GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glPixelTransferi (GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glPixelZoom (GLfloat xfactor, GLfloat yfactor);
	WINGDIAPI void APIENTRY glPointSize (GLfloat size);
	WINGDIAPI void APIENTRY glPolygonMode (GLenum face, GLenum mode);
	WINGDIAPI void APIENTRY glPolygonOffset (GLfloat factor, GLfloat units);
	WINGDIAPI void APIENTRY glPolygonStipple (const GLubyte *mask);
	WINGDIAPI void APIENTRY glPopAttrib (void);
	WINGDIAPI void APIENTRY glPopClientAttrib (void);
	WINGDIAPI void APIENTRY glPopMatrix (void);
	WINGDIAPI void APIENTRY glPopName (void);
	WINGDIAPI void APIENTRY glPrioritizeTextures (GLsizei n, const GLuint *textures, const GLclampf *priorities);
	WINGDIAPI void APIENTRY glPushAttrib (GLbitfield mask);
	WINGDIAPI void APIENTRY glPushClientAttrib (GLbitfield mask);
	WINGDIAPI void APIENTRY glPushMatrix (void);
	WINGDIAPI void APIENTRY glPushName (GLuint name);
	WINGDIAPI void APIENTRY glRasterPos2d (GLdouble x, GLdouble y);
	WINGDIAPI void APIENTRY glRasterPos2dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glRasterPos2f (GLfloat x, GLfloat y);
	WINGDIAPI void APIENTRY glRasterPos2fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glRasterPos2i (GLint x, GLint y);
	WINGDIAPI void APIENTRY glRasterPos2iv (const GLint *v);
	WINGDIAPI void APIENTRY glRasterPos2s (GLshort x, GLshort y);
	WINGDIAPI void APIENTRY glRasterPos2sv (const GLshort *v);
	WINGDIAPI void APIENTRY glRasterPos3d (GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glRasterPos3dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glRasterPos3f (GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glRasterPos3fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glRasterPos3i (GLint x, GLint y, GLint z);
	WINGDIAPI void APIENTRY glRasterPos3iv (const GLint *v);
	WINGDIAPI void APIENTRY glRasterPos3s (GLshort x, GLshort y, GLshort z);
	WINGDIAPI void APIENTRY glRasterPos3sv (const GLshort *v);
	WINGDIAPI void APIENTRY glRasterPos4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	WINGDIAPI void APIENTRY glRasterPos4dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glRasterPos4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	WINGDIAPI void APIENTRY glRasterPos4fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glRasterPos4i (GLint x, GLint y, GLint z, GLint w);
	WINGDIAPI void APIENTRY glRasterPos4iv (const GLint *v);
	WINGDIAPI void APIENTRY glRasterPos4s (GLshort x, GLshort y, GLshort z, GLshort w);
	WINGDIAPI void APIENTRY glRasterPos4sv (const GLshort *v);
	WINGDIAPI void APIENTRY glReadBuffer (GLenum mode);
	WINGDIAPI void APIENTRY glReadPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels);
	WINGDIAPI void APIENTRY glRectd (GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
	WINGDIAPI void APIENTRY glRectdv (const GLdouble *v1, const GLdouble *v2);
	WINGDIAPI void APIENTRY glRectf (GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	WINGDIAPI void APIENTRY glRectfv (const GLfloat *v1, const GLfloat *v2);
	WINGDIAPI void APIENTRY glRecti (GLint x1, GLint y1, GLint x2, GLint y2);
	WINGDIAPI void APIENTRY glRectiv (const GLint *v1, const GLint *v2);
	WINGDIAPI void APIENTRY glRects (GLshort x1, GLshort y1, GLshort x2, GLshort y2);
	WINGDIAPI void APIENTRY glRectsv (const GLshort *v1, const GLshort *v2);
	WINGDIAPI GLint APIENTRY glRenderMode (GLenum mode);
	WINGDIAPI void APIENTRY glRotated (GLdouble angle, GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glRotatef (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glScaled (GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glScalef (GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glScissor (GLint x, GLint y, GLsizei width, GLsizei height);
	WINGDIAPI void APIENTRY glSelectBuffer (GLsizei size, GLuint *buffer);
	WINGDIAPI void APIENTRY glShadeModel (GLenum mode);
	WINGDIAPI void APIENTRY glStencilFunc (GLenum func, GLint ref, GLuint mask);
	WINGDIAPI void APIENTRY glStencilMask (GLuint mask);
	WINGDIAPI void APIENTRY glStencilOp (GLenum fail, GLenum zfail, GLenum zpass);
	WINGDIAPI void APIENTRY glTexCoord1d (GLdouble s);
	WINGDIAPI void APIENTRY glTexCoord1dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord1f (GLfloat s);
	WINGDIAPI void APIENTRY glTexCoord1fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord1i (GLint s);
	WINGDIAPI void APIENTRY glTexCoord1iv (const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord1s (GLshort s);
	WINGDIAPI void APIENTRY glTexCoord1sv (const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoord2d (GLdouble s, GLdouble t);
	WINGDIAPI void APIENTRY glTexCoord2dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord2f (GLfloat s, GLfloat t);
	WINGDIAPI void APIENTRY glTexCoord2fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord2i (GLint s, GLint t);
	WINGDIAPI void APIENTRY glTexCoord2iv (const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord2s (GLshort s, GLshort t);
	WINGDIAPI void APIENTRY glTexCoord2sv (const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoord3d (GLdouble s, GLdouble t, GLdouble r);
	WINGDIAPI void APIENTRY glTexCoord3dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord3f (GLfloat s, GLfloat t, GLfloat r);
	WINGDIAPI void APIENTRY glTexCoord3fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord3i (GLint s, GLint t, GLint r);
	WINGDIAPI void APIENTRY glTexCoord3iv (const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord3s (GLshort s, GLshort t, GLshort r);
	WINGDIAPI void APIENTRY glTexCoord3sv (const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoord4d (GLdouble s, GLdouble t, GLdouble r, GLdouble q);
	WINGDIAPI void APIENTRY glTexCoord4dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glTexCoord4f (GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	WINGDIAPI void APIENTRY glTexCoord4fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glTexCoord4i (GLint s, GLint t, GLint r, GLint q);
	WINGDIAPI void APIENTRY glTexCoord4iv (const GLint *v);
	WINGDIAPI void APIENTRY glTexCoord4s (GLshort s, GLshort t, GLshort r, GLshort q);
	WINGDIAPI void APIENTRY glTexCoord4sv (const GLshort *v);
	WINGDIAPI void APIENTRY glTexCoordPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glTexEnvf (GLenum target, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glTexEnvfv (GLenum target, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glTexEnvi (GLenum target, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glTexEnviv (GLenum target, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glTexGend (GLenum coord, GLenum pname, GLdouble param);
	WINGDIAPI void APIENTRY glTexGendv (GLenum coord, GLenum pname, const GLdouble *params);
	WINGDIAPI void APIENTRY glTexGenf (GLenum coord, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glTexGenfv (GLenum coord, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glTexGeni (GLenum coord, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glTexGeniv (GLenum coord, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glTexImage1D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTexImage2D (GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTexParameterf (GLenum target, GLenum pname, GLfloat param);
	WINGDIAPI void APIENTRY glTexParameterfv (GLenum target, GLenum pname, const GLfloat *params);
	WINGDIAPI void APIENTRY glTexParameteri (GLenum target, GLenum pname, GLint param);
	WINGDIAPI void APIENTRY glTexParameteriv (GLenum target, GLenum pname, const GLint *params);
	WINGDIAPI void APIENTRY glTexSubImage1D (GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels);
	WINGDIAPI void APIENTRY glTranslated (GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glTranslatef (GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glVertex2d (GLdouble x, GLdouble y);
	WINGDIAPI void APIENTRY glVertex2dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glVertex2f (GLfloat x, GLfloat y);
	WINGDIAPI void APIENTRY glVertex2fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glVertex2i (GLint x, GLint y);
	WINGDIAPI void APIENTRY glVertex2iv (const GLint *v);
	WINGDIAPI void APIENTRY glVertex2s (GLshort x, GLshort y);
	WINGDIAPI void APIENTRY glVertex2sv (const GLshort *v);
	WINGDIAPI void APIENTRY glVertex3d (GLdouble x, GLdouble y, GLdouble z);
	WINGDIAPI void APIENTRY glVertex3dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glVertex3f (GLfloat x, GLfloat y, GLfloat z);
	WINGDIAPI void APIENTRY glVertex3fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glVertex3i (GLint x, GLint y, GLint z);
	WINGDIAPI void APIENTRY glVertex3iv (const GLint *v);
	WINGDIAPI void APIENTRY glVertex3s (GLshort x, GLshort y, GLshort z);
	WINGDIAPI void APIENTRY glVertex3sv (const GLshort *v);
	WINGDIAPI void APIENTRY glVertex4d (GLdouble x, GLdouble y, GLdouble z, GLdouble w);
	WINGDIAPI void APIENTRY glVertex4dv (const GLdouble *v);
	WINGDIAPI void APIENTRY glVertex4f (GLfloat x, GLfloat y, GLfloat z, GLfloat w);
	WINGDIAPI void APIENTRY glVertex4fv (const GLfloat *v);
	WINGDIAPI void APIENTRY glVertex4i (GLint x, GLint y, GLint z, GLint w);
	WINGDIAPI void APIENTRY glVertex4iv (const GLint *v);
	WINGDIAPI void APIENTRY glVertex4s (GLshort x, GLshort y, GLshort z, GLshort w);
	WINGDIAPI void APIENTRY glVertex4sv (const GLshort *v);
	WINGDIAPI void APIENTRY glVertexPointer (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
	WINGDIAPI void APIENTRY glViewport (GLint x, GLint y, GLsizei width, GLsizei height);

	/* EXT_vertex_array */
	typedef void (APIENTRY * PFNGLARRAYELEMENTEXTPROC) (GLint i);
	typedef void (APIENTRY * PFNGLDRAWARRAYSEXTPROC) (GLenum mode, GLint first, GLsizei count);
	typedef void (APIENTRY * PFNGLVERTEXPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLNORMALPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLCOLORPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLINDEXPOINTEREXTPROC) (GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLTEXCOORDPOINTEREXTPROC) (GLint size, GLenum type, GLsizei stride, GLsizei count, const GLvoid *pointer);
	typedef void (APIENTRY * PFNGLEDGEFLAGPOINTEREXTPROC) (GLsizei stride, GLsizei count, const GLboolean *pointer);
	typedef void (APIENTRY * PFNGLGETPOINTERVEXTPROC) (GLenum pname, GLvoid* *params);
	typedef void (APIENTRY * PFNGLARRAYELEMENTARRAYEXTPROC)(GLenum mode, GLsizei count, const GLvoid* pi);

	/* WIN_draw_range_elements */
	typedef void (APIENTRY * PFNGLDRAWRANGEELEMENTSWINPROC) (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices);

	/* WIN_swap_hint */
	typedef void (APIENTRY * PFNGLADDSWAPHINTRECTWINPROC)  (GLint x, GLint y, GLsizei width, GLsizei height);

	/* EXT_paletted_texture */
	typedef void (APIENTRY * PFNGLCOLORTABLEEXTPROC)(GLenum target, GLenum internalFormat, GLsizei width, GLenum format, GLenum type, const GLvoid *data);
	typedef void (APIENTRY * PFNGLCOLORSUBTABLEEXTPROC)(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data);
	typedef void (APIENTRY * PFNGLGETCOLORTABLEEXTPROC)(GLenum target, GLenum format, GLenum type, GLvoid *data);
	typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERIVEXTPROC)(GLenum target, GLenum pname, GLint *params);
	typedef void (APIENTRY * PFNGLGETCOLORTABLEPARAMETERFVEXTPROC)(GLenum target, GLenum pname, GLfloat *params);

	DGEAPI void glActiveTexture      (GLenum texture);
//	DGEAPI void glAlphaFuncx         (GLenum func, GLclampx ref);									¡æ glAlphaFunc
//	DGEAPI void glClearColorx        (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha); ¡æ glClearColor
	DGEAPI void glClearDepthf        (GLclampf depth);
//	DGEAPI void glClearDepthx        (GLclampx depth);												¡æ glClearDepthf

	DGEAPI void glClientActiveTexture(GLenum texture);
//	DGEAPI void glColor4x            (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);		¡æ glColor4f
	DGEAPI void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
	DGEAPI void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
	DGEAPI void glDepthRangef        (GLclampf nearValue, GLclampf farValue);

//	DGEAPI void glDepthRangex        (GLclampx nearValue, GLclampx farValue);				¡æ glDepthRangef
//	DGEAPI void glFogx               (GLenum pname, GLfixed param);							¡æ glFogf
//	DGEAPI void glFogxv              (GLenum pname, const GLfixed* params);					¡æ glFogfv
	DGEAPI void glFrustumf           (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val);
//	DGEAPI void glFrustumx           (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val);	¡æ glFrustumf

//	DGEAPI void glLightx             (GLenum light, GLenum pname, GLfixed param);			¡æ glLightf
//	DGEAPI void glLightxv            (GLenum light, GLenum pname, const GLfixed* params);	¡æ glLightfv
//	DGEAPI void glLightModelx        (GLenum pname, GLfixed param);							¡æ glLightModelf
//	DGEAPI void glLightModelxv       (GLenum pname, const GLfixed* params);					¡æ glLightModelfv
//	DGEAPI void glLineWidthx         (GLfixed width);										¡æ glLineWidth

//	DGEAPI void glLoadMatrixx        (const GLfixed* m);									¡æ glLoadMatrixf
//	DGEAPI void glMaterialx          (GLenum face, GLenum pname, GLfixed param);			¡æ glMaterialf
//	DGEAPI void glMaterialxv         (GLenum face, GLenum pname, const GLfixed* params);	¡æ glMaterialfv
	DGEAPI void glMultiTexCoord4f    (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
//	DGEAPI void glMultiTexCoord4x    (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);¡æ glMultiTexCoord4f

//	DGEAPI void glMultMatrixx        (const GLfixed* m);									¡æ glMultMatrixf
//	DGEAPI void glNormal3x           (GLfixed nx, GLfixed ny, GLfixed nz);					¡æ glNormal3f
	DGEAPI void glOrthof             (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val);
//	DGEAPI void glOrthox             (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val); ¡æ glOrthof
//	DGEAPI void glPointSizex         (GLfixed size);										¡æ glPointSizef

//	DGEAPI void glPolygonOffsetx     (GLfixed factor, GLfixed units);						¡æ glPolygonOffsetf
//	DGEAPI void glRotatex            (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);		¡æ glRotatef
	DGEAPI void glSampleCoverage     (GLclampf value, GLboolean invert);
//	DGEAPI void glSampleCoveragex    (GLclampx value, GLboolean invert);					¡æ glSampleCoverage
//	DGEAPI void glScalex             (GLfixed x, GLfixed y, GLfixed z);						¡æ glScalef

//	DGEAPI void glTexEnvx            (GLenum target, GLenum pname, GLfixed param);			¡æ glTexEnvf
//	DGEAPI void glTexEnvxv           (GLenum target, GLenum pname, const GLfixed* params);	¡æ glTexEnvfv
//	DGEAPI void glTexParameterx      (GLenum target, GLenum pname, GLfixed param);			¡æ glTexParameterf
//	DGEAPI void glTranslatex         (GLfixed x, GLfixed y, GLfixed z);						¡æ glTranslatef
	DGEAPI void glBindBuffer         (GLenum target, GLuint buffer);

	DGEAPI void glBufferData         (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
	DGEAPI void glBufferSubData      (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
	DGEAPI void glCurrentPaletteMatrixOES(GLuint matrix);
	DGEAPI void glDeleteBuffers      (GLsizei n, const GLuint* buffers);
	DGEAPI void glGenBuffers         (GLsizei n, GLuint* buffers);

	DGEAPI void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params);
	DGEAPI void glGetClipPlanef      (GLenum plane, GLfloat* equation);
//	DGEAPI void glGetClipPlanex      (GLenum plane, GLfixed* equation);					¡æ glGetClipPlanef
//	DGEAPI void glGetFixedv          (GLenum pname, GLfixed* params);					¡æ glGetFloatv
//	DGEAPI void glGetLightxv         (GLenum light, GLenum pname, GLfixed* params);		¡æ glGetLightfv

//	DGEAPI void glGetMaterialxv      (GLenum face, GLenum pname, GLfixed* params);		¡æ glGetMaterialfv
//	DGEAPI void glGetTexEnvxv        (GLenum target, GLenum pname, GLfixed* params);	¡æ glGetTexEnvfv
//	DGEAPI void glGetTexParameterxv  (GLenum target, GLenum pname, GLfixed* params);	¡æ glGetTexParameterfv
	DGEAPI int  glIsBuffer           (GLuint buffer);
	DGEAPI void glMatrixIndexPointerOES(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);

	DGEAPI void glWeightPointerOES   (GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
	DGEAPI void glClipPlanef         (GLenum plane, const GLfloat* equation);
//	DGEAPI void glClipPlanex         (GLenum plane, const GLfixed* equation);			¡æ glClipPlanef
	DGEAPI void glPointSizePointerOES(GLenum type, GLsizei stride, const GLvoid* pointer);

	DGEAPI void glPointParameterfv   (GLenum pname, const GLfloat* params);
//	DGEAPI void glPointParameterxv   (GLenum pname, const GLfixed* params);				¡æ glPointParameterfv
	DGEAPI void glPointParameterf    (GLenum pname, GLfloat params);
//	DGEAPI void glPointParameterx    (GLenum pname, GLfixed params);					¡æ glPointParameterf
//	DGEAPI void glTexParameterxv     (GLenum target, GLenum pname, const GLfixed* param);¡æglTexParameterfv
#else

	GL_APICALL void             glActiveTexture         (GLenum texture);
	GL_APICALL void             glAlphaFunc             (GLenum func, GLclampf ref);
	GL_APICALL void             glAlphaFuncx            (GLenum func, GLclampx ref);
	GL_APICALL void             glBindTexture           (GLenum target, GLuint texture);
	GL_APICALL void             glBlendFunc             (GLenum sfactor, GLenum dfactor);
	GL_APICALL void             glClear                 (GLbitfield mask);
	GL_APICALL void             glClearColor            (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	GL_APICALL void             glClearColorx           (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);
	GL_APICALL void             glClearDepthf           (GLclampf depth);
	GL_APICALL void             glClearDepthx           (GLclampx depth);
	GL_APICALL void             glClearStencil          (GLint s);
	GL_APICALL void             glClientActiveTexture   (GLenum texture);
	GL_APICALL void             glColor4f               (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	GL_APICALL void             glColor4x               (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);
	GL_APICALL void             glColorMask             (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	GL_APICALL void             glColorPointer          (GLint size, GLenum type, GLsizei stride, const GLvoid* ptr);
	GL_APICALL void             glCompressedTexImage2D  (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
	GL_APICALL void             glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
	GL_APICALL void             glCopyTexImage2D        (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
	GL_APICALL void             glCopyTexSubImage2D     (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	GL_APICALL void             glCullFace              (GLenum mode);
	GL_APICALL void             glDeleteTextures        (GLsizei n, const GLuint* textures);
	GL_APICALL void             glDepthFunc             (GLenum func);
	GL_APICALL void             glDepthMask             (GLboolean flag);
	GL_APICALL void             glDepthRangef           (GLclampf nearValue, GLclampf farValue);
	GL_APICALL void             glDepthRangex           (GLclampx nearValue, GLclampx farValue);
	GL_APICALL void             glDisable               (GLenum cap);
	GL_APICALL void             glDisableClientState    (GLenum cap);
	GL_APICALL void             glDrawArrays            (GLenum mode, GLint first, GLsizei count);
	GL_APICALL void             glDrawElements          (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
	GL_APICALL void             glEnable                (GLenum cap);
	GL_APICALL void             glEnableClientState     (GLenum cap);
	GL_APICALL void             glFinish                (void);
	GL_APICALL void             glFlush                 (void);
	GL_APICALL void             glFogf                  (GLenum pname, GLfloat param);
	GL_APICALL void             glFogfv                 (GLenum pname, const GLfloat* params);
	GL_APICALL void             glFogx                  (GLenum pname, GLfixed param);
	GL_APICALL void             glFogxv                 (GLenum pname, const GLfixed* params);
	GL_APICALL void             glFrontFace             (GLenum mode);
	GL_APICALL void             glFrustumf              (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val);
	GL_APICALL void             glFrustumx              (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val);
	GL_APICALL void             glGenTextures           (GLsizei n, GLuint* textures);
	GL_APICALL GLenum           glGetError              (void);
	GL_APICALL void             glGetIntegerv           (GLenum pname, GLint* params);
	GL_APICALL const GLubyte*   glGetString             (GLenum name);
	GL_APICALL void             glHint                  (GLenum target, GLenum mode);
	GL_APICALL void             glLightf                (GLenum light, GLenum pname, GLfloat param);
	GL_APICALL void             glLightfv               (GLenum light, GLenum pname, const GLfloat* params);
	GL_APICALL void             glLightx                (GLenum light, GLenum pname, GLfixed param);
	GL_APICALL void             glLightxv               (GLenum light, GLenum pname, const GLfixed* params);
	GL_APICALL void             glLightModelf           (GLenum pname, GLfloat param);
	GL_APICALL void             glLightModelfv          (GLenum pname, const GLfloat* params);
	GL_APICALL void             glLightModelx           (GLenum pname, GLfixed param);
	GL_APICALL void             glLightModelxv          (GLenum pname, const GLfixed* params);
	GL_APICALL void             glLineWidth             (GLfloat width);
	GL_APICALL void             glLineWidthx            (GLfixed width);
	GL_APICALL void             glLoadIdentity          (void);
	GL_APICALL void             glLoadMatrixf           (const GLfloat* m);
	GL_APICALL void             glLoadMatrixx           (const GLfixed* m);
	GL_APICALL void             glLogicOp               (GLenum opcode);
	GL_APICALL void             glMaterialf             (GLenum face, GLenum pname, GLfloat param);
	GL_APICALL void             glMaterialfv            (GLenum face, GLenum pname, const GLfloat* params);
	GL_APICALL void             glMaterialx             (GLenum face, GLenum pname, GLfixed param);
	GL_APICALL void             glMaterialxv            (GLenum face, GLenum pname, const GLfixed* params);
	GL_APICALL void             glMatrixMode            (GLenum mode);
	GL_APICALL void             glMultiTexCoord4f       (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
	GL_APICALL void             glMultiTexCoord4x       (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);
	GL_APICALL void             glMultMatrixf           (const GLfloat* m);
	GL_APICALL void             glMultMatrixx           (const GLfixed* m);
	GL_APICALL void             glNormal3f              (GLfloat nx, GLfloat ny, GLfloat nz);
	GL_APICALL void             glNormal3x              (GLfixed nx, GLfixed ny, GLfixed nz);
	GL_APICALL void             glNormalPointer         (GLenum type, GLsizei stride, const GLvoid* ptr);
	GL_APICALL void             glOrthof                (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val);
	GL_APICALL void             glOrthox                (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val);
	GL_APICALL void             glPixelStorei           (GLenum pname, GLint param);
	GL_APICALL void             glPointSize             (GLfloat size);
	GL_APICALL void             glPointSizex            (GLfixed size);
	GL_APICALL void             glPolygonOffset         (GLfloat factor, GLfloat units);
	GL_APICALL void             glPolygonOffsetx        (GLfixed factor, GLfixed units);
	GL_APICALL void             glPopMatrix             (void);
	GL_APICALL void             glPushMatrix            (void);
	GL_APICALL void             glReadPixels            (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
	GL_APICALL void             glRotatef               (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
	GL_APICALL void             glRotatex               (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);
	GL_APICALL void             glSampleCoverage        (GLclampf value, GLboolean invert);
	GL_APICALL void             glSampleCoveragex       (GLclampx value, GLboolean invert);
	GL_APICALL void             glScalef                (GLfloat x, GLfloat y, GLfloat z);
	GL_APICALL void             glScalex                (GLfixed x, GLfixed y, GLfixed z);
	GL_APICALL void             glScissor               (GLint x, GLint y, GLsizei width, GLsizei height);
	GL_APICALL void             glShadeModel            (GLenum mode);
	GL_APICALL void             glStencilFunc           (GLenum func, GLint ref, GLuint mask);
	GL_APICALL void             glStencilMask           (GLuint mask);
	GL_APICALL void             glStencilOp             (GLenum fail, GLenum zfail, GLenum zpass);
	GL_APICALL void             glTexCoordPointer       (GLint size, GLenum type, GLsizei stride, const GLvoid* ptr);
	GL_APICALL void             glTexEnvf               (GLenum target, GLenum pname, GLfloat param);
	GL_APICALL void             glTexEnvfv              (GLenum target, GLenum pname, const GLfloat* params);
	GL_APICALL void             glTexEnvx               (GLenum target, GLenum pname, GLfixed param);
	GL_APICALL void             glTexEnvxv              (GLenum target, GLenum pname, const GLfixed* params);
	GL_APICALL void             glTexImage2D            (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
	GL_APICALL void             glTexParameterf         (GLenum target, GLenum pname, GLfloat param);
	GL_APICALL void             glTexParameterx         (GLenum target, GLenum pname, GLfixed param);
	GL_APICALL void             glTexSubImage2D         (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
	GL_APICALL void             glTranslatef            (GLfloat x, GLfloat y, GLfloat z);
	GL_APICALL void             glTranslatex            (GLfixed x, GLfixed y, GLfixed z);
	GL_APICALL void             glVertexPointer         (GLint size, GLenum type, GLsizei stride, const GLvoid* ptr);
	GL_APICALL void             glViewport              (GLint x, GLint y, GLsizei width, GLsizei height);


	#if defined(GERBERA_ES_1_1)
		GL_APICALL void             glBindBuffer                            (GLenum target, GLuint buffer);
		GL_APICALL void             glBufferData                            (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
		GL_APICALL void             glBufferSubData                         (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
		GL_APICALL void             glColor4ub                              (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);
		GL_APICALL void             glCurrentPaletteMatrixOES               (GLuint matrix);
		GL_APICALL void             glDeleteBuffers                         (GLsizei n, const GLuint* buffers);
		GL_APICALL void             glGenBuffers                            (GLsizei n, GLuint* buffers);
		GL_APICALL void             glGetBooleanv                           (GLenum pname, GLboolean* params);
		GL_APICALL void             glGetBufferParameteriv                  (GLenum target, GLenum pname, GLint* params);
		GL_APICALL void             glGetClipPlanef                         (GLenum plane, GLfloat* equation);
		GL_APICALL void             glGetClipPlanex                         (GLenum plane, GLfixed* equation);
		GL_APICALL void             glGetFloatv                             (GLenum pname, GLfloat* params);
		GL_APICALL void             glGetFixedv                             (GLenum pname, GLfixed* params);
		GL_APICALL void             glGetLightfv                            (GLenum light, GLenum pname, GLfloat* params);
		GL_APICALL void             glGetLightxv                            (GLenum light, GLenum pname, GLfixed* params);
		GL_APICALL void             glGetMaterialfv                         (GLenum face, GLenum pname, GLfloat* params);
		GL_APICALL void             glGetMaterialxv                         (GLenum face, GLenum pname, GLfixed* params);
		GL_APICALL void             glGetPointerv                           (GLenum pname, GLvoid** params);
		GL_APICALL void             glGetTexEnvfv                           (GLenum target, GLenum pname, GLfloat* params);
		GL_APICALL void             glGetTexEnviv                           (GLenum target, GLenum pname, GLint* params);
		GL_APICALL void             glGetTexEnvxv                           (GLenum target, GLenum pname, GLfixed* params);
		GL_APICALL void             glGetTexParameteriv                     (GLenum target, GLenum pname, GLint* params);
		GL_APICALL void             glGetTexParameterfv                     (GLenum target, GLenum pname, GLfloat* params);
		GL_APICALL void             glGetTexParameterxv                     (GLenum target, GLenum pname, GLfixed* params);
		GL_APICALL GLboolean        glIsEnabled                             (GLenum cap);
		GL_APICALL GLboolean        glIsTexture                             (GLuint texture);
		GL_APICALL GLboolean        glIsBuffer                              (GLuint buffer);
		GL_APICALL void             glLoadPaletteFromModelViewMatrixOES     (void);
		GL_APICALL void             glMatrixIndexPointerOES                 (GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
		GL_APICALL void             glWeightPointerOES                      (GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
		GL_APICALL void             glClipPlanef                            (GLenum plane, const GLfloat* equation);
		GL_APICALL void             glClipPlanex                            (GLenum plane, const GLfixed* equation);
		GL_APICALL void             glPointSizePointerOES                   (GLenum type, GLsizei stride, const GLvoid* pointer);
		GL_APICALL void             glPointParameterfv                      (GLenum pname, const GLfloat* params);
		GL_APICALL void             glPointParameterxv                      (GLenum pname, const GLfixed* params);
		GL_APICALL void             glPointParameterf                       (GLenum pname, GLfloat params);
		GL_APICALL void             glPointParameterx                       (GLenum pname, GLfixed params);
		GL_APICALL void             glDrawTexfOES                           (GLfloat sx, GLfloat sy, GLfloat sz, GLfloat sw, GLfloat sh);
		GL_APICALL void             glDrawTexxOES                           (GLfixed sx, GLfixed sy, GLfixed sz, GLfixed sw, GLfixed sh);
		GL_APICALL void             glDrawTexiOES                           (GLint sx, GLint sy, GLint sz, GLint sw, GLint sh);
		GL_APICALL void             glDrawTexsOES                           (GLshort sx, GLshort sy, GLshort sz, GLshort sw, GLshort sh);
		GL_APICALL void             glDrawTexfvOES                          (GLfloat* params);
		GL_APICALL void             glDrawTexxvOES                          (GLfixed* params);
		GL_APICALL void             glDrawTexivOES                          (GLint* params);
		GL_APICALL void             glDrawTexsvOES                          (GLshort* params);
		GL_APICALL void             glTexParameteri                         (GLenum target, GLenum pname, GLint param);
		GL_APICALL void             glTexParameterfv                        (GLenum target, GLenum pname, const GLfloat* param);
		GL_APICALL void             glTexParameterxv                        (GLenum target, GLenum pname, const GLfixed* param);
		GL_APICALL void             glTexParameteriv                        (GLenum target, GLenum pname, const GLint* param);
	#endif /* GERBERA_ES_1_1 */


	/*-------------------------------------------------------------------------
	 * Extensions
	 *-----------------------------------------------------------------------*/

	GL_APICALL GLbitfield       glQueryMatrixxOES       (GLfixed mantissa[16], GLint exponent[16]);

#endif


#if defined (__cplusplus)
}
#endif

/*-----------------------------------------------------------------------*/
#endif /* __gl_h_ */



