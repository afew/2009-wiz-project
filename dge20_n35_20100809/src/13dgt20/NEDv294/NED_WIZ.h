#ifndef _NED_WIZ_H_
#define _NED_WIZ_H_

#ifdef  __cplusplus
extern "C" {
#endif

#define WIZ_VID	    0x0525
#define WIZ_PID	    0xA4A5
#define	SYS_PATH    "/var/tmp/"

int sng(unsigned int x, unsigned int y);
int com_drm_time(unsigned char* securetime);
int set_drm_time(unsigned char* securetime);

#ifdef  __cplusplus
}
#endif

#endif
