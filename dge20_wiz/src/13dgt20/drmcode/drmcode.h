#ifndef __DRMCODE_H__
#define __DRMCODE_H__

#ifdef __cplusplus
extern "C" {
#endif

extern inline void getcode(unsigned char buf[32]);
extern inline void getserial(unsigned char buf[24]);
extern inline void setrandnum(unsigned char buf[4]);
extern inline void getrandnum(unsigned char buf[4]);
extern inline void setsecuretime(unsigned char buf[8]);
extern inline void getsecuretime(unsigned char buf[8]);

#ifdef __cplusplus
} /* ends extern "C" */
#endif

#endif
