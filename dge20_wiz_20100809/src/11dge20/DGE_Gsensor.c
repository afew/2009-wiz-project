// Implementation of the DGE G-sensor.
//
////////////////////////////////////////////////////////////////////////////////


#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

#else

	#include <signal.h>

	#include "te9_tf9_hybrid_driver.h"
	#include "te9_tf9_regs.h"

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



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




#include "DGE_Gsensor.h"





static int g_fdDgeGsensor;

#if defined(_WIN32) || defined(WIN32)

#else
	struct sigaction g_SigAct, g_SigOld;
#endif

/* Signal Handler... */
static void irqChecker_sigHandler(int signo)
{
#if defined(_WIN32) || defined(WIN32)

#else
	switch(signo)
	{
	case SIGIO:
//		printf("-I- SIGIO \n");
		KIONIX_ACCEL_service_interrupt();
		break;
	case SIGINT: case SIGQUIT:
		printf("-I- SIGINT or SIGQUIT \n");
		break;
	}

#endif
}


// Sig Action Function Initialization.
int init_sigact(int fd)
{
#if defined(_WIN32) || defined(WIN32)
	printf("Not Implemented in this Device\n");

#else
	int oflag;

	g_SigAct.sa_handler = irqChecker_sigHandler;
	sigemptyset(&g_SigAct.sa_mask);
	g_SigAct.sa_flags = SA_INTERRUPT;

	if(sigaction(SIGIO, &g_SigAct, &g_SigOld) < 0)
	{
		printf("-W- can't receive SIGIO event\n");
		return DGE_EFAIL;
	}

	fcntl(fd, F_SETOWN, getpid());
	oflag = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflag | FASYNC);
#endif


	return DGE_OK;
}


// Device File Initialization.
int DGE_GsensorOpen()
{
	if(g_fdDgeGsensor>=0)
		return DGE_OK;

#if defined(_WIN32) || defined(WIN32)

	printf("Not Implemented in this Device\n");

#else
	// blocking mode open...
	g_fdDgeGsensor = open("/dev/accel", O_RDWR);

	if (g_fdDgeGsensor <0)
	{
		printf("-E- Error opening accel adapter\n");
		return DGE_EFAIL;
	}

	if(init_sigact(g_fdDgeGsensor) <0)
	{
		DGE_GsensorClose();
		printf("Failed Binding Gsensor Device to Signal\n");
		return DGE_EFAIL;
	}
#endif

	return DGE_OK;
}

int DGE_GsensorClose()
{
#if defined(_WIN32) || defined(WIN32)

	printf("Not Implemented in this Device\n");

#else
	KIONIX_ACCEL_deinit();

	if(g_fdDgeGsensor<0)
		return DGE_OK;

	close(g_fdDgeGsensor);
	g_fdDgeGsensor = -1;

#endif

	return DGE_OK;
}


// Setup Environment
int DGE_GsensorSetEnv(DGE_GSENSOR_ENV* p)
{
#if defined(_WIN32) || defined(WIN32)

	printf("Not Implemented in this Device\n");

#else
	int device_type;
	int hr =0;

	KIONIX_ACCEL_init();

	// set sensor to sleep mode
	KIONIX_ACCEL_sleep();

	//check device type...
	device_type = KIONIX_ACCEL_get_device_type();

	if(device_type != DEVICE_TYPE_KIONIX_KXTF9)
	{
		printf("Wrong device type, val: %d\n", device_type);
	}

	KIONIX_ACCEL_deinit();



	//set registers...
	hr = KXTF9_set_G_range(p->Range);			//2-g range

	if(hr)
	{
		printf("Setup G range Failed\n");
		printf("%d\n", p->Range);
		return DGE_EFAIL;
	}

	hr = KXTF9_set_resolution(p->Resolution); 	// for using tap function

	if(hr)
	{
		printf("Setup G Resolution Failed\n");
		return DGE_EFAIL;
	}

	KIONIX_ACCEL_int_activeh();
	KIONIX_ACCEL_int_latch();



	//directional - tap

	hr =KXTF9_set_odr_tap(p->TapHz);		// 400 HZ
	if(hr)
	{
		printf("Setup directional tap Failed\n");
		return DGE_EFAIL;
	}

	//KXTF9_tap_unmask_TFU();
	//KXTF9_tap_unmask_TFD();
	//KXTF9_tap_unmask_TUP();
	//KXTF9_tap_unmask_TDO();

	KXTF9_tap_mask_TLE();
	KXTF9_tap_mask_TRI();
	KXTF9_tap_mask_TDO();
	KXTF9_tap_mask_TUP();
	KXTF9_tap_mask_TFD();
	KXTF9_tap_mask_TFU();

	//KXTF9_tap_mask_TFU();		// Face Up/Down Tap Detection...
	//KXTF9_tap_mask_TFD();
	//KXTF9_tap_mask_TUP();		// Up/Down Tap Detection...
	//KXTF9_tap_mask_TDO();




	KXTF9_tap_mask_TRI();		// 좌우(X+/-) 방향에대한 Tap Detection...
	KXTF9_tap_mask_TLE();
	KXTF9_enable_tap_detection();



	//Screen Rotation
	hr = KXTF9_set_odr_tilt(p->TiltHz);
	if(hr)
	{
		printf("Setup tilt Failed\n");
		return DGE_EFAIL;
	}


	hr = KIONIX_ACCEL_tilt_timer(p->TiltTimer);	//rotation sensitivity...
	if(hr)
	{
		printf("Setup Tilt Time Failed\n");
		return DGE_EFAIL;
	}


	KIONIX_ACCEL_position_unmask_fu();	//Face up/down 에 대해서 disable..
	KIONIX_ACCEL_position_unmask_fd();
	//KIONIX_ACCEL_position_mask_fu();	//Face up/down 에 대해서 disable..
	//KIONIX_ACCEL_position_mask_fd();
	KIONIX_ACCEL_position_mask_up();
	KIONIX_ACCEL_position_mask_do();
	KIONIX_ACCEL_position_mask_ri();
	KIONIX_ACCEL_position_mask_le();
	KIONIX_ACCEL_enable_tilt_function();

	//interrupt enable and operating start
	KIONIX_ACCEL_enable_interrupt();
	KIONIX_ACCEL_enable_outputs();		//enable acceleration data output

#endif

	return DGE_OK;
}


// Read data from g-sensor
int DGE_GsensorRead(DGE_GSENSOR_VAL* p)
{
#if defined(_WIN32) || defined(WIN32)

	printf("Not Implemented in this Device\n");
	// 데이터 초기화
	p->x	 = DGE_GSN_DEFAULT;
	p->y	 = DGE_GSN_DEFAULT;
	p->z	 = DGE_GSN_DEFAULT;
	p->TapMod= DGE_GSN_DEFAULT;
	p->TapDir= DGE_GSN_DEFAULT;

#else
	int hr;
	unsigned char tap_mode ;
	char status_reg=0, int_rel=0;

	char int_src_reg1, int_src_reg2;


	// 데이터 초기화
	p->x	 = DGE_GSN_DEFAULT;
	p->y	 = DGE_GSN_DEFAULT;
	p->z	 = DGE_GSN_DEFAULT;
	p->TapMod= DGE_GSN_DEFAULT;
	p->TapDir= DGE_GSN_DEFAULT;


	hr = KIONIX_ACCEL_read_LPF_g(&(p->x), &(p->y), &(p->z));

	if(hr)
		return DGE_EFAIL;

	if(0 == KIONIX_ACCEL_get_device_type())
		return DGE_OK;



	// Tap Event는 Interrupt를 사용해야 함

	// Locking.
	KX_INTLOCK( );

	// 인터럽트 해제
	KIONIX_ACCEL_disable_interrupt();

	// 인터럽트가 발생했는지 확인
	KIONIX_ACCEL_read_bytes(KIONIX_ACCEL_I2C_STATUS_REG, &status_reg, 1);

//	printf("-W- status_reg (0x%02x) \n", status_reg);

	// 인터럽트가 있으면 꺼내옴.
	if((status_reg & BIT(4))  )
	{
//		printf("-W- no interrupt event (0x%02x) \n", status_reg);


		KIONIX_ACCEL_read_bytes(KXTF9_I2C_INT_SRC_REG1, &int_src_reg1, 1);
		KIONIX_ACCEL_read_bytes(KXTF9_I2C_INT_SRC_REG2, &int_src_reg2, 1);

		// Direction tap
		if(int_src_reg2 & (0x3<<2) )
		{
			tap_mode = ((int_src_reg2&(0x3<<2))>>2);
			//KIONIX_ACCEL_process_directional_tap(tap_mode, int_src_reg1); // tap_mode(single/dobule), tap_direction

			p->TapMod= tap_mode;
			p->TapDir= int_src_reg1;
		}
	}


	KIONIX_ACCEL_read_bytes(KIONIX_ACCEL_I2C_INT_REL, &int_rel, 1);

	// 인터럽트 다시 활성화
	KIONIX_ACCEL_enable_interrupt();

	KX_INTFREE( );

#endif

	return DGE_OK;
}



