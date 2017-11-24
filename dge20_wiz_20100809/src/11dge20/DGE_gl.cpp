// Implementation of the IDGE_Device.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
#if _MSC_VER >= 1200
#pragma warning(disable: 4996)
#endif

#include <windows.h>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gles/gl.h>
#include <gles/egl.h>

#include <DGE_Math.h>



//GL_APICALL void             glAlphaFunc             (GLenum func, GLclampf ref);									// OpenGL 1.3
//GL_APICALL void             glAlphaFuncx            (GLenum func, GLclampx ref);									// Redefine glAlphaFunc
//GL_APICALL void             glBindTexture           (GLenum target, GLuint texture);								// OpenGL 1.3

//GL_APICALL void             glActiveTexture         (GLenum texture);												// GLAPI void APIENTRY glActiveTextureARB (GLenum);
//GL_APICALL void             glAlphaFunc             (GLenum func, GLclampf ref);									// OpenGL 1.3
//GL_APICALL void             glAlphaFuncx            (GLenum func, GLclampx ref);									// Redefine glAlphaFunc
//GL_APICALL void             glBindTexture           (GLenum target, GLuint texture);								// OpenGL 1.3
//GL_APICALL void             glBlendFunc             (GLenum sfactor, GLenum dfactor);								// OpenGL 1.3
//GL_APICALL void             glClear                 (GLbitfield mask);											// OpenGL 1.3
//GL_APICALL void             glClearColor            (GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);// OpenGL 1.3
//GL_APICALL void             glClearColorx           (GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha);// Redefine glClearColor
//GL_APICALL void             glClearDepthf           (GLclampf depth);												// OpenGL 1.3 glClearDepth
//GL_APICALL void             glClearDepthx           (GLclampx depth);												// Redefine glClearDepth
//GL_APICALL void             glClearStencil          (GLint s);													// OpenGL 1.3
//GL_APICALL void             glClientActiveTexture   (GLenum texture);												// GLAPI void APIENTRY glClientActiveTextureARB (GLenum);

//GL_APICALL void             glColor4f               (GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);	// OpenGL 1.3
//GL_APICALL void             glColor4x               (GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha);	// Redefine glColor4x

//GL_APICALL void             glColorMask             (GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);	// OpenGL 1.3
//GL_APICALL void             glColorPointer          (GLint size, GLenum type, GLsizei stride, const GLvoid* ptr);			// OpenGL 1.3

//GL_APICALL void             glCompressedTexImage2D  (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);			// GLAPI void APIENTRY glCompressedTexImage2DARB (GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid *);
//GL_APICALL void             glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);	// GLAPI void APIENTRY glCompressedTexSubImage2DARB (GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid *);
//GL_APICALL void             glCopyTexImage2D        (GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);		// OpenGL 1.3
//GL_APICALL void             glCopyTexSubImage2D     (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);				// OpenGL 1.3

//GL_APICALL void             glCullFace              (GLenum mode);														// OpenGL 1.3
//GL_APICALL void             glDeleteTextures        (GLsizei n, const GLuint* textures);									// OpenGL 1.3
//GL_APICALL void             glDepthFunc             (GLenum func);														// OpenGL 1.3
//GL_APICALL void             glDepthMask             (GLboolean flag);														// OpenGL 1.3
//GL_APICALL void             glDepthRangef           (GLclampf nearValue, GLclampf farValue);								// OpenGL 1.3 glDepthRange
//GL_APICALL void             glDepthRangex           (GLclampx nearValue, GLclampx farValue);								// Redefine GlDeptRange
//GL_APICALL void             glDisable               (GLenum cap);															// OpenGL 1.3
//GL_APICALL void             glDisableClientState    (GLenum cap);															// OpenGL 1.3
//GL_APICALL void             glDrawArrays            (GLenum mode, GLint first, GLsizei count);							// OpenGL 1.3
//GL_APICALL void             glDrawElements          (GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);		// OpenGL 1.3
//GL_APICALL void             glEnable                (GLenum cap);															// OpenGL 1.3
//GL_APICALL void             glEnableClientState     (GLenum cap);															// OpenGL 1.3
//GL_APICALL void             glFinish                (void);																// OpenGL 1.3
//GL_APICALL void             glFlush                 (void);																// OpenGL 1.3
//GL_APICALL void             glFogf                  (GLenum pname, GLfloat param);										// OpenGL 1.3
//GL_APICALL void             glFogfv                 (GLenum pname, const GLfloat* params);								// OpenGL 1.3
//GL_APICALL void             glFogx                  (GLenum pname, GLfixed param);										// Redefine glFogf
//GL_APICALL void             glFogxv                 (GLenum pname, const GLfixed* params);								// Redefine glFogfv
//GL_APICALL void             glFrontFace             (GLenum mode);														// OpenGL 1.3
//GL_APICALL void             glFrustumf              (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val);	// OpenGL 1.3 glFrustum
//GL_APICALL void             glFrustumx              (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val);	// OpenGL 1.3 glFrustum
//GL_APICALL void             glGenTextures           (GLsizei n, GLuint* textures);								// OpenGL 1.3
//GL_APICALL GLenum           glGetError              (void);														// OpenGL 1.3
//GL_APICALL void             glGetIntegerv           (GLenum pname, GLint* params);								// OpenGL 1.3
//GL_APICALL const GLubyte*   glGetString             (GLenum name);												// OpenGL 1.3

//GL_APICALL void             glHint                  (GLenum target, GLenum mode);									// OpenGL 1.3
//GL_APICALL void             glLightf                (GLenum light, GLenum pname, GLfloat param);					// OpenGL 1.3
//GL_APICALL void             glLightfv               (GLenum light, GLenum pname, const GLfloat* params);			// OpenGL 1.3
//GL_APICALL void             glLightx                (GLenum light, GLenum pname, GLfixed param);					// Redefine glLightf
//GL_APICALL void             glLightxv               (GLenum light, GLenum pname, const GLfixed* params);			// Redefine glLightfv
//GL_APICALL void             glLightModelf           (GLenum pname, GLfloat param);								// OpenGL 1.3
//GL_APICALL void             glLightModelfv          (GLenum pname, const GLfloat* params);						// OpenGL 1.3
//GL_APICALL void             glLightModelx           (GLenum pname, GLfixed param);								// Redefine glLightModelf
//GL_APICALL void             glLightModelxv          (GLenum pname, const GLfixed* params);						// Redefine glLightModelxv
//GL_APICALL void             glLineWidth             (GLfloat width);												// OpenGL 1.3
//GL_APICALL void             glLineWidthx            (GLfixed width);												// Redefine glLineWidth
//GL_APICALL void             glLoadIdentity          (void);														// OpenGL 1.3
//GL_APICALL void             glLoadMatrixf           (const GLfloat* m);											// OpenGL 1.3
//GL_APICALL void             glLoadMatrixx           (const GLfixed* m);											// Redefine glLoadMatrixf

//GL_APICALL void             glLogicOp               (GLenum opcode);												// OpenGL 1.3
//GL_APICALL void             glMaterialf             (GLenum face, GLenum pname, GLfloat param);					// OpenGL 1.3
//GL_APICALL void             glMaterialfv            (GLenum face, GLenum pname, const GLfloat* params);			// OpenGL 1.3
//GL_APICALL void             glMaterialx             (GLenum face, GLenum pname, GLfixed param);					// Redefine glMaterialf
//GL_APICALL void             glMaterialxv            (GLenum face, GLenum pname, const GLfixed* params);			// Redefine glMaterialfv
//GL_APICALL void             glMatrixMode            (GLenum mode);												// OpenGL 1.3
//GL_APICALL void             glMultiTexCoord4f       (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);	// GLAPI void APIENTRY glMultiTexCoord4fARB (GLenum, GLfloat, GLfloat, GLfloat, GLfloat);
//GL_APICALL void             glMultiTexCoord4x       (GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q);	// Redefine glMultiTexCoord4f

//GL_APICALL void             glMultMatrixf           (const GLfloat* m);											// OpenGL 1.3
//GL_APICALL void             glMultMatrixx           (const GLfixed* m);											// Redefine glMultMatrixf
//GL_APICALL void             glNormal3f              (GLfloat nx, GLfloat ny, GLfloat nz);							// OpenGL 1.3
//GL_APICALL void             glNormal3x              (GLfixed nx, GLfixed ny, GLfixed nz);							// Redefine glNormal3f
//GL_APICALL void             glNormalPointer         (GLenum type, GLsizei stride, const GLvoid* ptr);				// OpenGL 1.3

//GL_APICALL void             glOrthof                (GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val);	// OpenGL 1.3 glOrtho
//GL_APICALL void             glOrthox                (GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val);	// Redefine glOrtho
//GL_APICALL void             glPixelStorei           (GLenum pname, GLint param);									// OpenGL 1.3
//GL_APICALL void             glPointSize             (GLfloat size);												// OpenGL 1.3
//GL_APICALL void             glPointSizex            (GLfixed size);												// glPointSizex
//GL_APICALL void             glPolygonOffset         (GLfloat factor, GLfloat units);								// OpenGL 1.3
//GL_APICALL void             glPolygonOffsetx        (GLfixed factor, GLfixed units);								// OpenGL 1.3
//GL_APICALL void             glPopMatrix             (void);														// OpenGL 1.3
//GL_APICALL void             glPushMatrix            (void);														// OpenGL 1.3
//GL_APICALL void             glReadPixels            (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);	// OpenGL 1.3

//GL_APICALL void             glRotatef               (GLfloat angle, GLfloat x, GLfloat y, GLfloat z);				// OpenGL 1.3
//GL_APICALL void             glRotatex               (GLfixed angle, GLfixed x, GLfixed y, GLfixed z);				// Redefine glRotatef
//GL_APICALL void             glSampleCoverage        (GLclampf value, GLboolean invert);							// GLAPI void APIENTRY glSampleCoverageARB (GLclampf, GLboolean);
//GL_APICALL void             glSampleCoveragex       (GLclampx value, GLboolean invert);							// Redefine glSampleCoverage
//GL_APICALL void             glScalef                (GLfloat x, GLfloat y, GLfloat z);							// OpenGL 1.3
//GL_APICALL void             glScalex                (GLfixed x, GLfixed y, GLfixed z);							// Redefine glScalef

//GL_APICALL void             glScissor               (GLint x, GLint y, GLsizei width, GLsizei height);			// OpenGL 1.3
//GL_APICALL void             glShadeModel            (GLenum mode);												// OpenGL 1.3
//GL_APICALL void             glStencilFunc           (GLenum func, GLint ref, GLuint mask);						// OpenGL 1.3
//GL_APICALL void             glStencilMask           (GLuint mask);												// OpenGL 1.3
//GL_APICALL void             glStencilOp             (GLenum fail, GLenum zfail, GLenum zpass);					// OpenGL 1.3
//GL_APICALL void             glTexCoordPointer       (GLint size, GLenum type, GLsizei stride, const GLvoid* ptr);	// OpenGL 1.3

//GL_APICALL void             glTexEnvf               (GLenum target, GLenum pname, GLfloat param);					// OpenGL 1.3
//GL_APICALL void             glTexEnvfv              (GLenum target, GLenum pname, const GLfloat* params);			// OpenGL 1.3
//GL_APICALL void             glTexEnvx               (GLenum target, GLenum pname, GLfixed param);					// Redefine glTexEnvf
//GL_APICALL void             glTexEnvxv              (GLenum target, GLenum pname, const GLfixed* params);			// Redefine glTexEnvfv

//GL_APICALL void             glTexImage2D            (GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);	// OpenGL 1.3
//GL_APICALL void             glTexParameterf         (GLenum target, GLenum pname, GLfloat param);					// OpenGL 1.3
//GL_APICALL void             glTexParameterx         (GLenum target, GLenum pname, GLfixed param);					// Redefine GlTexParameterf
//GL_APICALL void             glTexSubImage2D         (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);		// OpenGL 1.3
//GL_APICALL void             glTranslatef            (GLfloat x, GLfloat y, GLfloat z);							// OpenGL 1.3
//GL_APICALL void             glTranslatex            (GLfixed x, GLfixed y, GLfixed z);							// Redefine glTranslatef
//GL_APICALL void             glVertexPointer         (GLint size, GLenum type, GLsizei stride, const GLvoid* ptr);	// OpenGL 1.3
//GL_APICALL void             glViewport              (GLint x, GLint y, GLsizei width, GLsizei height);			// OpenGL 1.3
//
//
//#if defined(GERBERA_ES_1_1)
//    GL_APICALL void       glBindBuffer                        (GLenum target, GLuint buffer);											// GLAPI void APIENTRY glBindBufferARB (GLenum, GLuint);
//    GL_APICALL void       glBufferData                        (GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);		// GLAPI void APIENTRY glBufferDataARB (GLenum, GLsizeiptrARB, const GLvoid *, GLenum);
//    GL_APICALL void       glBufferSubData                     (GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);	// GLAPI void APIENTRY glBufferSubDataARB (GLenum, GLintptrARB, GLsizeiptrARB, const GLvoid *);
//    GL_APICALL void       glColor4ub                          (GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha);				// OpenGL 1.3

//    GL_APICALL void       glCurrentPaletteMatrixOES           (GLuint matrix);								// GLAPI void APIENTRY glCurrentPaletteMatrixARB (GLint);
//    GL_APICALL void       glDeleteBuffers                     (GLsizei n, const GLuint* buffers);				// GLAPI void APIENTRY glDeleteBuffersARB (GLsizei, const GLuint *);
//    GL_APICALL void       glGenBuffers                        (GLsizei n, GLuint* buffers);					// GLAPI void APIENTRY glGenBuffersARB (GLsizei, GLuint *);
//    GL_APICALL void       glGetBooleanv                       (GLenum pname, GLboolean* params);				// OpenGL 1.3
//    GL_APICALL void       glGetBufferParameteriv              (GLenum target, GLenum pname, GLint* params);	// GLAPI void APIENTRY glGetBufferParameterivARB (GLenum, GLenum, GLint *);

//    GL_APICALL void       glGetClipPlanef                     (GLenum plane, GLfloat* equation);				// OpenGL 1.3 glGetClipPlane
//    GL_APICALL void       glGetClipPlanex                     (GLenum plane, GLfixed* equation);				// Redefine glGetClipPlane
//    GL_APICALL void       glGetFloatv                         (GLenum pname, GLfloat* params);				// OpenGL 1.3
//    GL_APICALL void       glGetFixedv                         (GLenum pname, GLfixed* params);				// Redefine glGetFloatv
//    GL_APICALL void       glGetLightfv                        (GLenum light, GLenum pname, GLfloat* params);	// OpenGL 1.3
//    GL_APICALL void       glGetLightxv                        (GLenum light, GLenum pname, GLfixed* params);	// Redefine glGetLightf

//    GL_APICALL void       glGetMaterialfv                     (GLenum face, GLenum pname, GLfloat* params);	// OpenGL 1.3
//    GL_APICALL void       glGetMaterialxv                     (GLenum face, GLenum pname, GLfixed* params);	// Redefine glGetMaterialfv
//    GL_APICALL void       glGetPointerv                       (GLenum pname, GLvoid** params);				// OpenGL 1.3
//    GL_APICALL void       glGetTexEnvfv                       (GLenum target, GLenum pname, GLfloat* params);	// OpenGL 1.3
//    GL_APICALL void       glGetTexEnviv                       (GLenum target, GLenum pname, GLint* params);	// OpenGL 1.3
//    GL_APICALL void       glGetTexEnvxv                       (GLenum target, GLenum pname, GLfixed* params);	// OpenGL 1.3

//    GL_APICALL void       glGetTexParameteriv                 (GLenum target, GLenum pname, GLint* params);	// OpenGL 1.3
//    GL_APICALL void       glGetTexParameterfv                 (GLenum target, GLenum pname, GLfloat* params);	// OpenGL 1.3
//    GL_APICALL void       glGetTexParameterxv                 (GLenum target, GLenum pname, GLfixed* params);	// Redefine glGetTexParameterfv
//    GL_APICALL GLboolean  glIsEnabled                         (GLenum cap);									// OpenGL 1.3
//    GL_APICALL GLboolean  glIsTexture                         (GLuint texture);								// OpenGL 1.3
//    GL_APICALL GLboolean  glIsBuffer                          (GLuint buffer);								// GLAPI GLboolean APIENTRY glIsBuffer (GLuint);

//    GL_APICALL void       glLoadPaletteFromModelViewMatrixOES (void);											// ES 전용

//    GL_APICALL void       glMatrixIndexPointerOES             (GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);	// GLAPI void APIENTRY glMatrixIndexPointerARB (GLint, GLenum, GLsizei, const GLvoid *);
//    GL_APICALL void       glWeightPointerOES                  (GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);	// GLAPI void APIENTRY glWeightPointerARB (GLint, GLenum, GLsizei, const GLvoid *);
//    GL_APICALL void       glClipPlanef                        (GLenum plane, const GLfloat* equation);		// OpenGL 1.3 glClipPlane
//    GL_APICALL void       glClipPlanex                        (GLenum plane, const GLfixed* equation);		// Redefine glClipPlane

//    GL_APICALL void       glPointSizePointerOES               (GLenum type, GLsizei stride, const GLvoid* pointer);	// ES 전용
//    GL_APICALL void       glPointParameterfv                  (GLenum pname, const GLfloat* params);			// GLAPI void APIENTRY glPointParameterfvARB (GLenum, const GLfloat *);
//    GL_APICALL void       glPointParameterxv                  (GLenum pname, const GLfixed* params);			// Redefine glPointParameterfv
//    GL_APICALL void       glPointParameterf                   (GLenum pname, GLfloat params);					// GLAPI void APIENTRY glPointParameterfARB (GLenum, GLfloat);
//    GL_APICALL void       glPointParameterx                   (GLenum pname, GLfixed params);					// Redefine glPointParameterf

//    GL_APICALL void       glDrawTexfOES                       (GLfloat sx, GLfloat sy, GLfloat sz, GLfloat sw, GLfloat sh);	// ES 전용
//    GL_APICALL void       glDrawTexxOES                       (GLfixed sx, GLfixed sy, GLfixed sz, GLfixed sw, GLfixed sh);	// ES 전용
//    GL_APICALL void       glDrawTexiOES                       (GLint sx, GLint sy, GLint sz, GLint sw, GLint sh);				// ES 전용
//    GL_APICALL void       glDrawTexsOES                       (GLshort sx, GLshort sy, GLshort sz, GLshort sw, GLshort sh);	// ES 전용
//    GL_APICALL void       glDrawTexfvOES                      (GLfloat* params);												// ES 전용
//    GL_APICALL void       glDrawTexxvOES                      (GLfixed* params);												// ES 전용
//    GL_APICALL void       glDrawTexivOES                      (GLint* params);												// ES 전용
//    GL_APICALL void       glDrawTexsvOES                      (GLshort* params);												// ES 전용

//    GL_APICALL void       glTexParameteri                     (GLenum target, GLenum pname, GLint param);						// OpenGL 1.3
//    GL_APICALL void       glTexParameterfv                    (GLenum target, GLenum pname, const GLfloat* param);			// OpenGL 1.3
//    GL_APICALL void       glTexParameterxv                    (GLenum target, GLenum pname, const GLfixed* param);			// Redefine glTexParameterfv
//    GL_APICALL void       glTexParameteriv                    (GLenum target, GLenum pname, const GLint* param);				// OpenGL 1.3
//#endif /* GERBERA_ES_1_1 */

//GL_APICALL GLbitfield       glQueryMatrixxOES       (GLfixed mantissa[16], GLint exponent[16]);								// ES 전용



#ifndef APIENTRYP
#define APIENTRYP APIENTRY *
#endif


typedef void (APIENTRYP PFNGLACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLCLIENTACTIVETEXTUREARBPROC) (GLenum texture);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DARBPROC) (GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data);
typedef void (APIENTRYP PFNGLMULTITEXCOORD4FARBPROC) (GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q);
typedef void (APIENTRYP PFNGLSAMPLECOVERAGEARBPROC) (GLclampf value, GLboolean invert);
typedef void (APIENTRYP PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
typedef void (APIENTRYP PFNGLBUFFERDATAARBPROC) (GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
typedef void (APIENTRYP PFNGLCURRENTPALETTEMATRIXARBPROC) (GLint index);
typedef void (APIENTRYP PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);

typedef void (APIENTRYP PFNGLBUFFERSUBDATAARBPROC) (GLenum target, GLsizeiptr offset, GLsizeiptr size, const GLvoid *data);
typedef void (APIENTRYP PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
typedef void (APIENTRYP PFNGLGETBUFFERPARAMETERIVARBPROC) (GLenum target, GLenum pname, GLint *params);
typedef void (APIENTRYP PFNGLMATRIXINDEXPOINTERARBPROC) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRYP PFNGLWEIGHTPOINTERARBPROC) (GLint size, GLenum type, GLsizei stride, const GLvoid *pointer);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFVARBPROC) (GLenum pname, const GLfloat *params);
typedef void (APIENTRYP PFNGLPOINTPARAMETERFARBPROC) (GLenum pname, GLfloat param);
typedef GLboolean (APIENTRYP PFNGLISBUFFERARBPROC) (GLuint buffer);


PFNGLACTIVETEXTUREARBPROC			glActiveTextureARB				= NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC		glClientActiveTextureARB		= NULL;
PFNGLCOMPRESSEDTEXIMAGE2DARBPROC	glCompressedTexImage2DARB		= NULL;
PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC	glCompressedTexSubImage2DARB	= NULL;
PFNGLMULTITEXCOORD4FARBPROC			glMultiTexCoord4fARB			= NULL;
PFNGLSAMPLECOVERAGEARBPROC			glSampleCoverageARB				= NULL;
PFNGLBINDBUFFERARBPROC				glBindBufferARB					= NULL;
PFNGLBUFFERDATAARBPROC				glBufferDataARB					= NULL;
PFNGLCURRENTPALETTEMATRIXARBPROC	glCurrentPaletteMatrixARB		= NULL;
PFNGLDELETEBUFFERSARBPROC			glDeleteBuffersARB				= NULL;

PFNGLBUFFERSUBDATAARBPROC			glBufferSubDataARB				= NULL;
PFNGLGENBUFFERSARBPROC				glGenBuffersARB					= NULL;
PFNGLGETBUFFERPARAMETERIVARBPROC	glGetBufferParameterivARB		= NULL;
PFNGLMATRIXINDEXPOINTERARBPROC		glMatrixIndexPointerARB			= NULL;
PFNGLWEIGHTPOINTERARBPROC			glWeightPointerARB				= NULL;
PFNGLPOINTPARAMETERFVARBPROC		glPointParameterfvARB			= NULL;
PFNGLPOINTPARAMETERFARBPROC			glPointParameterfARB			= NULL;
PFNGLISBUFFERARBPROC				glIsBufferARB					= NULL;




INT DGE_glInit()
{
	glActiveTextureARB				= (PFNGLACTIVETEXTUREARBPROC			)wglGetProcAddress("glActiveTextureARB");
	glClientActiveTextureARB		= (PFNGLCLIENTACTIVETEXTUREARBPROC		)wglGetProcAddress("glClientActiveTextureARB");
	glCompressedTexImage2DARB		= (PFNGLCOMPRESSEDTEXIMAGE2DARBPROC		)wglGetProcAddress("glCompressedTexImage2DARB");
	glCompressedTexSubImage2DARB	= (PFNGLCOMPRESSEDTEXSUBIMAGE2DARBPROC	)wglGetProcAddress("glCompressedTexSubImage2DARB");
	glMultiTexCoord4fARB			= (PFNGLMULTITEXCOORD4FARBPROC			)wglGetProcAddress("glMultiTexCoord4fARB");
	glSampleCoverageARB				= (PFNGLSAMPLECOVERAGEARBPROC			)wglGetProcAddress("glSampleCoverageARB");
	glBindBufferARB					= (PFNGLBINDBUFFERARBPROC				)wglGetProcAddress("glBindBufferARB");
	glBufferDataARB					= (PFNGLBUFFERDATAARBPROC				)wglGetProcAddress("glBufferDataARB");
	glCurrentPaletteMatrixARB		= (PFNGLCURRENTPALETTEMATRIXARBPROC		)wglGetProcAddress("glCurrentPaletteMatrixARB");
	glDeleteBuffersARB				= (PFNGLDELETEBUFFERSARBPROC			)wglGetProcAddress("glDeleteBuffersARB");

	glBufferSubDataARB				= (PFNGLBUFFERSUBDATAARBPROC			)wglGetProcAddress("glBufferSubDataARB");
	glGenBuffersARB					= (PFNGLGENBUFFERSARBPROC				)wglGetProcAddress("glGenBuffersARB");
	glGetBufferParameterivARB		= (PFNGLGETBUFFERPARAMETERIVARBPROC		)wglGetProcAddress("glGetBufferParameterivARB");
	glMatrixIndexPointerARB			= (PFNGLMATRIXINDEXPOINTERARBPROC		)wglGetProcAddress("glMatrixIndexPointerARB");
	glWeightPointerARB				= (PFNGLWEIGHTPOINTERARBPROC			)wglGetProcAddress("glWeightPointerARB");
	glPointParameterfvARB			= (PFNGLPOINTPARAMETERFVARBPROC			)wglGetProcAddress("glPointParameterfvARB");
	glPointParameterfARB			= (PFNGLPOINTPARAMETERFARBPROC			)wglGetProcAddress("glPointParameterfARB");
	glIsBufferARB					= (PFNGLISBUFFERARBPROC					)wglGetProcAddress("glIsBufferARB");

	if(NULL == glActiveTextureARB || NULL == glClientActiveTextureARB || NULL == glBindBufferARB || NULL == glGenBuffersARB)
	{
		printf("Sorry !!! This device cannot be emulating.\n");
		return -1;
	}

	return 0;
}










void glAlphaFuncx(GLenum func, GLclampx ref)
{
	glAlphaFunc(func, FloatFromFixed(ref));
}

void glActiveTexture(GLenum texture)
{
	if(NULL == glActiveTextureARB)
	{
		printf("Err: Call glActiveTextureARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glActiveTextureARB(texture);
}

void glClearColorx(GLclampx red, GLclampx green, GLclampx blue, GLclampx alpha)
{
	glClearColor( FloatFromFixed(red), FloatFromFixed(green), FloatFromFixed(blue), FloatFromFixed(alpha) );
}

void glClearDepthf(GLclampf depth)
{
	glClearDepth((GLclampd)depth);
}

void glClearDepthx(GLclampx depth)
{
	glClearDepth((GLclampd)FloatFromFixed(depth));
}

void glClientActiveTexture(GLenum texture)
{
	if(NULL == glClientActiveTextureARB)
	{
		printf("Err: Call glClientActiveTextureARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glClientActiveTextureARB(texture);
}

void glColor4x(GLfixed red, GLfixed green, GLfixed blue, GLfixed alpha)
{
	glColor4f((GLfloat)FloatFromFixed(red), (GLfloat)FloatFromFixed(green), (GLfloat)FloatFromFixed(blue), (GLfloat)FloatFromFixed(alpha));	// Redefine glColor4x
}


void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
	if(NULL == glCompressedTexImage2DARB)
	{
		printf("Err: Call glCompressedTexImage2DARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glCompressedTexImage2DARB(target, level, internalformat, width, height, border, imageSize, data);
}

void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
	if(NULL == glCompressedTexSubImage2DARB)
	{
		printf("Err: Call glCompressedTexSubImage2DARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glCompressedTexSubImage2DARB(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void glDepthRangef(GLclampf nearValue, GLclampf farValue)
{
	glDepthRange((GLclampd)nearValue, (GLclampd)farValue);
}

void glDepthRangex(GLclampx nearValue, GLclampx farValue)
{
	glDepthRange((GLclampd)FloatFromFixed(nearValue), (GLclampd)FloatFromFixed(farValue) );
}

void glFogx(GLenum pname, GLfixed param)
{
	glFogf(pname, FloatFromFixed(param) );
}

void glFogxv(GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glFogfv(pname, param );
}

void glFrustumf(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val)
{
	glFrustum((GLdouble)left, (GLdouble)right, (GLdouble)bottom, (GLdouble)top, (GLdouble)near_val, (GLdouble)far_val);
}

void glFrustumx(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val)
{
	glFrustum((GLdouble)FloatFromFixed(left), (GLdouble)FloatFromFixed(right), (GLdouble)FloatFromFixed(bottom), (GLdouble)FloatFromFixed(top), (GLdouble)FloatFromFixed(near_val), (GLdouble)FloatFromFixed(far_val));
}


void glLightx(GLenum light, GLenum pname, GLfixed param)
{
	glLightf(light, pname, FloatFromFixed(param) );
}


void glLightxv(GLenum light, GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glLightfv(light, pname, param);
}


void glLightModelx(GLenum pname, GLfixed param)
{
	glLightModelf(pname, FloatFromFixed(param) );
}


void glLightModelxv(GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glLightModelfv(pname, param);
}


void glLineWidthx(GLfixed width)
{
	glLineWidth(FloatFromFixed(width) );
}


void glLoadMatrixx(const GLfixed* m)
{
	GLfloat	param[16]={0};

	for(int i=0; i<16; ++i)
		param[i] = FloatFromFixed(m[i]);

	glLoadMatrixf(param);
}


void glMaterialx(GLenum face, GLenum pname, GLfixed param)
{
	glMaterialf(face, pname, FloatFromFixed(param) );
}


void glMaterialxv(GLenum face, GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glMaterialfv(face, pname, param);
}


void glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
	if(NULL == glMultiTexCoord4fARB)
	{
		printf("Err: Call glMultiTexCoord4fARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glMultiTexCoord4fARB(target, s, t, r, q);
}


void glMultiTexCoord4x(GLenum target, GLfixed s, GLfixed t, GLfixed r, GLfixed q)
{
	if(NULL == glMultiTexCoord4fARB)
	{
		printf("Err: Call glMultiTexCoord4fARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}
	
	glMultiTexCoord4fARB(target, FloatFromFixed(s), FloatFromFixed(t), FloatFromFixed(r), FloatFromFixed(q) );
}


void glMultMatrixx(const GLfixed* m)
{
	GLfloat	param[16]={0};

	for(int i=0; i<16; ++i)
		param[i] = FloatFromFixed(m[i]);

	glMultMatrixf(param);
}


void glNormal3x(GLfixed nx, GLfixed ny, GLfixed nz)
{
	glNormal3f(FloatFromFixed(nx), FloatFromFixed(ny), FloatFromFixed(nz) );
}


void glOrthof(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top, GLfloat near_val, GLfloat far_val)
{
	glOrtho((GLdouble)left, (GLdouble)right, (GLdouble)bottom, (GLdouble)top, (GLdouble)near_val, (GLdouble)far_val);
}


void glOrthox(GLfixed left, GLfixed right, GLfixed bottom, GLfixed top, GLfixed near_val, GLfixed far_val)
{
	glOrtho((GLdouble)FloatFromFixed(left), (GLdouble)FloatFromFixed(right), (GLdouble)FloatFromFixed(bottom), (GLdouble)FloatFromFixed(top), (GLdouble)FloatFromFixed(near_val), (GLdouble)FloatFromFixed(far_val) );
}


void glPointSizex(GLfixed size)
{
	glPointSize(FloatFromFixed(size));
}

void glPolygonOffsetx(GLfixed factor, GLfixed units)
{
	glPolygonOffset(FloatFromFixed(factor), FloatFromFixed(units));
}

void glRotatex(GLfixed angle, GLfixed x, GLfixed y, GLfixed z)
{
	glRotatef(FloatFromFixed(angle), FloatFromFixed(x), FloatFromFixed(y), FloatFromFixed(z) );
}


void glSampleCoverage(GLclampf value, GLboolean invert)
{
	if(NULL == glSampleCoverageARB)
	{
		printf("Err: Call glSampleCoverageARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glSampleCoverageARB(value, invert);
}

void glSampleCoveragex(GLclampx value, GLboolean invert)
{

	if(NULL == glSampleCoverageARB)
	{
		printf("Err: Call glSampleCoverageARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glSampleCoverageARB(FloatFromFixed(value), invert);
}


void glScalex(GLfixed x, GLfixed y, GLfixed z)
{
	glScalef(FloatFromFixed(x), FloatFromFixed(y), FloatFromFixed(z));
}


void glTexEnvx(GLenum target, GLenum pname, GLfixed param)
{
	glTexEnvf(target, pname, FloatFromFixed(param) );
}


void glTexEnvxv(GLenum target, GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glTexEnvfv(target, pname, param);
}

void glTexParameterx(GLenum target, GLenum pname, GLfixed param)
{
	glTexParameterf(target, pname, FloatFromFixed(param) );
}


void glTranslatex(GLfixed x, GLfixed y, GLfixed z)
{
	glTranslatef(FloatFromFixed(x), FloatFromFixed(y), FloatFromFixed(z) );
}


void glBindBuffer(GLenum target, GLuint buffer)
{
	if(NULL == glBindBufferARB)
	{
		printf("Err: Call glBindBufferARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glBindBufferARB(target, buffer);
}


void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
	if(NULL == glBufferDataARB)
	{
		printf("Err: Call glBufferDataARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glBufferDataARB(target, size, data, usage);
}


void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
	if(NULL == glBufferSubDataARB)
	{
		printf("Err: Call glBufferSubDataARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glBufferSubDataARB(target, offset, size, data);
}


void glCurrentPaletteMatrixOES (GLuint matrix)
{
	if(NULL == glCurrentPaletteMatrixARB)
	{
		printf("Err: Call glCurrentPaletteMatrixARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glCurrentPaletteMatrixARB(matrix);
}


void glDeleteBuffers(GLsizei n, const GLuint* buffers)
{
	if(NULL == glDeleteBuffersARB)
	{
		printf("Err: Call glDeleteBuffersARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glDeleteBuffersARB(n, buffers);
}


void glGenBuffers(GLsizei n, GLuint* buffers)
{
	if(NULL == glGenBuffersARB)
	{
		printf("Err: Call glGenBuffersARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glGenBuffersARB(n, buffers);
}


void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
	if(NULL == glGetBufferParameterivARB)
	{
		printf("Err: Call glGetBufferParameterivARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glGetBufferParameterivARB(target, pname, params);
}


void glGetClipPlanef(GLenum plane, GLfloat* equation)
{
	GLdouble	param[8]={0};
	
	glGetClipPlane(plane, param);

	equation[0] = (GLfloat)param[0];
	equation[1] = (GLfloat)param[1];
	equation[2] = (GLfloat)param[2];
	equation[3] = (GLfloat)param[3];
}


void glGetClipPlanex(GLenum plane, GLfixed* equation)
{
	GLdouble	param[8]={0};

	glGetClipPlane(plane, param);

	equation[0] = Fixed(param[0]);
	equation[1] = Fixed(param[1]);
	equation[2] = Fixed(param[2]);
	equation[3] = Fixed(param[3]);
}


void glGetFixedv(GLenum pname, GLfixed* params)
{
	GLfloat	param[8]={0};

	glGetFloatv(pname, param);

	params[0] = Fixed(param[0]);
	params[1] = Fixed(param[1]);
	params[2] = Fixed(param[2]);
	params[3] = Fixed(param[3]);
}


void glGetLightxv(GLenum light, GLenum pname, GLfixed* params)
{
	GLfloat	param[8]={0};

	glGetLightfv(light, pname, param);

	params[0] = Fixed(param[0]);
	params[1] = Fixed(param[1]);
	params[2] = Fixed(param[2]);
	params[3] = Fixed(param[3]);
}


void glGetMaterialxv(GLenum face, GLenum pname, GLfixed* params)
{
	GLfloat	param[8]={0};

	glGetMaterialfv(face, pname, param);

	params[0] = Fixed(param[0]);
	params[1] = Fixed(param[1]);
	params[2] = Fixed(param[2]);
	params[3] = Fixed(param[3]);
}
	
void glGetTexEnvxv(GLenum target, GLenum pname, GLfixed* params)
{
	GLfloat	param[8]={0};

	glGetTexEnvfv(target, pname, param);

	params[0] = Fixed(param[0]);
	params[1] = Fixed(param[1]);
	params[2] = Fixed(param[2]);
	params[3] = Fixed(param[3]);
}


void glGetTexParameterxv(GLenum target, GLenum pname, GLfixed* params)
{
	GLfloat	param[8]={0};

	glGetTexParameterfv(target, pname, param);

	params[0] = Fixed(param[0]);
	params[1] = Fixed(param[1]);
	params[2] = Fixed(param[2]);
	params[3] = Fixed(param[3]);
}


int glIsBuffer(GLuint buffer)
{
	if(NULL == glIsBufferARB)
	{
		printf("Err: Call glIsBufferARB\n");
		printf("It is only supported on the GPH.\n");
		return 0;
	}

	return (int)glIsBufferARB(buffer);
}




void glMatrixIndexPointerOES(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	if(NULL == glMatrixIndexPointerARB)
	{
		printf("Err: Call glMatrixIndexPointerARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glMatrixIndexPointerARB(size, type, stride, pointer);
}


void glWeightPointerOES(GLint size, GLenum type, GLsizei stride, const GLvoid* pointer)
{
	if(NULL == glWeightPointerARB)
	{
		printf("Err: Call glWeightPointerARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glWeightPointerARB(size, type, stride, pointer);
}


void glClipPlanef(GLenum plane, const GLfloat* equation)
{
	GLdouble	param[8]={0};

	param[0] = (GLdouble)equation[0];
	param[1] = (GLdouble)equation[1];
	param[2] = (GLdouble)equation[2];
	param[3] = (GLdouble)equation[3];

	glClipPlane(plane, param);
}

void glClipPlanex(GLenum plane, const GLfixed* equation)
{
	GLdouble	param[8]={0};

	param[0] = (GLdouble)FloatFromFixed(equation[0]);
	param[1] = (GLdouble)FloatFromFixed(equation[1]);
	param[2] = (GLdouble)FloatFromFixed(equation[2]);
	param[3] = (GLdouble)FloatFromFixed(equation[3]);

	glClipPlane(plane, param);
}


void glPointSizePointerOES(GLenum type, GLsizei stride, const GLvoid* pointer)
{
	printf("It is only supported on the GPH.\n");
}


void glPointParameterfv(GLenum pname, const GLfloat* params)
{
	if(NULL == glPointParameterfvARB)
	{
		printf("Err: Call glPointParameterfvARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glPointParameterfvARB (pname, params);
}


void glPointParameterxv(GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	if(NULL == glPointParameterfvARB)
	{
		printf("Err: Call glMultiTexCoord4fARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glPointParameterfvARB (pname, param);
}


void glPointParameterf(GLenum pname, GLfloat params)
{
	if(NULL == glPointParameterfARB)
	{
		printf("Err: Call glMultiTexCoord4fARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glPointParameterfARB(pname, params);
}


void glPointParameterx(GLenum pname, GLfixed params)
{
	if(NULL == glPointParameterfARB)
	{
		printf("Err: Call glMultiTexCoord4fARB\n");
		printf("It is only supported on the GPH.\n");
		return;
	}

	glPointParameterfARB(pname, FloatFromFixed(params));
}


void glTexParameterxv(GLenum target, GLenum pname, const GLfixed* params)
{
	GLfloat	param[8]={0};

	param[0] = FloatFromFixed(params[0]);
	param[1] = FloatFromFixed(params[1]);
	param[2] = FloatFromFixed(params[2]);
	param[3] = FloatFromFixed(params[3]);

	glTexParameterfv(target, pname, param);
}

GLbitfield glQueryMatrixxOES(GLfixed mantissa[16], GLint exponent[16])
{
	printf("It is only supported on the GPH.\n");
	return 0;
}






INT EnumExtension(char* sCheck, char* sGetStrings)
{

	char*	sSrc= sGetStrings;
	char	seps[]   = " ";
	char*	token;

	token = strtok( sSrc, seps );
	while( token != NULL )
	{
		if(0 == _stricmp(sCheck, token))
			return 0;

		token = strtok( NULL, seps );
	}

	return -1;

//	sExtension
//	GL_ARB_multitexture
//	GL_EXT_texture_env_add
//	GL_EXT_compiled_vertex_array
//	GL_S3_s3tc
//	GL_ARB_depth_texture
//	GL_ARB_fragment_program
//	GL_ARB_fragment_program_shadow
//	GL_ARB_fragment_shader
//	GL_ARB_multisample
//	GL_ARB_occlusion_query
//	GL_ARB_point_param
}




EGLint eglGetError(void)
{
	return glGetError();
}


EGLDisplay  eglGetDisplay(NativeDisplayType displayID)
{
	HDC	hDC	= GetDC((HWND)displayID);
	return hDC;
}

EGLBoolean  eglTerminate(NativeDisplayType displayID, EGLDisplay dpy)
{
	HWND	hWnd = (HWND)displayID;
	HDC		hDC	= (HDC)dpy;

	ReleaseDC(hWnd, hDC);
	return true;
}


EGLBoolean  eglInitialize(EGLDisplay dpy, EGLint* major, EGLint* minor)
{
	// 아무것도 안함.
	*major = 1;
	*minor = 3;
	return true;
}





const char* eglQueryString(EGLDisplay dpy, EGLint name)
{
	printf("It is only supported on the GPH.\n");
	return NULL;
}


EGLBoolean  eglGetConfigs(EGLDisplay dpy, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	*num_config = 1;
	return true;
}


EGLBoolean  eglChooseConfig(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config)
{
	printf("It is only supported on the GPH.\n");
	return true;
}


EGLBoolean  eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint* value)
{
	printf("It is only supported on the GPH.\n");
	return true;
}


EGLSurface  eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, NativeWindowType win, const EGLint* attrib_list)
{
	HWND	hWnd = (HWND)win;
	HDC		hDC	= (HDC)dpy;


	PIXELFORMATDESCRIPTOR pfd = {0};
	pfd.nSize		= sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion	= 1;
	pfd.dwFlags		= PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |PFD_DOUBLEBUFFER;	//|PFD_GENERIC_ACCELERATED;
	pfd.iPixelType	= PFD_TYPE_RGBA;
	pfd.cColorBits	= 32;
	pfd.cDepthBits	= 16;
	pfd.cStencilBits=  0;
	pfd.iLayerType	= PFD_MAIN_PLANE;


	UINT PixelFormat = ChoosePixelFormat(hDC, &pfd);

	if(0 == PixelFormat)
		return NULL;

	if(0 == SetPixelFormat(hDC, PixelFormat,&pfd))
		return NULL;

	return hDC;
}


EGLBoolean  eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	// 아무것도 안함.
	printf("It is only supported on the GPH.\n");
	return true;
}


EGLContext  eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint* attrib_list)
{
	HDC		hDC	= (HDC)dpy;
	HGLRC	hRC = wglCreateContext(hDC);

	if(NULL == hRC)
		return NULL;

	return hRC;
}


EGLBoolean  eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	HGLRC	hRC	= (HGLRC)ctx;
	wglDeleteContext(hRC);
	return true;
}



EGLBoolean  eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	HDC		hDC	= (HDC)dpy;
	HGLRC	hRC	= (HGLRC)ctx;

	if(0 == wglMakeCurrent(hDC, hRC))
		return false;

	return true;
}


EGLBoolean  eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	HDC		hDC	= (HDC)dpy;
	SwapBuffers(hDC);
	return true;
}



EGLSurface  eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint* attrib_list)
{
	printf("It is only supported on the GPH.\n");
	return NULL;
}


EGLSurface  eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, NativePixmapType pixmap, const EGLint* attrib_list)
{
	printf("It is only supported on the GPH.\n");
	return NULL;
}





EGLBoolean  eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint* value)
{
	printf("It is only supported on the GPH.\n");
	return false;
}

EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	printf("It is only supported on the GPH.\n");
	return false;
}


EGLBoolean eglBindTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	printf("It is only supported on the GPH.\n");
	return false;
}


EGLBoolean eglReleaseTexImage(EGLDisplay dpy, EGLSurface surface, EGLint buffer)
{
	printf("It is only supported on the GPH.\n");
	return false;
}


EGLBoolean  eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	printf("It is only supported on the GPH.\n");
	return true;
}




EGLContext  eglGetCurrentContext(void)
{
	printf("It is only supported on the GPH.\n");
	return NULL;
}


EGLSurface  eglGetCurrentSurface(EGLint readdraw)
{
	printf("It is only supported on the GPH.\n");
	return NULL;
}

EGLDisplay  eglGetCurrentDisplay(void)
{
	printf("It is only supported on the GPH.\n");
	return NULL;
}


EGLBoolean  eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint* value)
{
	printf("It is only supported on the GPH.\n");
	return false;
}

EGLBoolean  eglWaitGL(void)
{
	printf("It is only supported on the GPH.\n");
	return true;
}


EGLBoolean  eglWaitNative(EGLint engine)
{
	printf("It is only supported on the GPH.\n");
	return true;
}


EGLBoolean  eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, NativePixmapType target)
{
	printf("It is only supported on the GPH.\n");
	return true;
}


//extern void (*eglGetProcAddress(const char *procname)) (void);


#endif



