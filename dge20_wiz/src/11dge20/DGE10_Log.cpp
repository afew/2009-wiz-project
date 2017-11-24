// Implementation of the DGE 1.0 Log.
//
////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) || defined(WIN32)
	#if _MSC_VER >= 1200
	#pragma warning(disable: 4996)
	#endif

	#include <io.h>
	#include <direct.h>

#else

	#include <unistd.h>
	#include <sys/stat.h>

#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <memory.h>

#include "DGE_Type.h"
#include "DGE_Util.h"



////////////////////////////////////////////////////////////////////////////////
// DGE File 1.0
class CDGE_Log : public IDGE_Log
{
public:
	static int			g_cDGELogEnable;
	static	IDGE_Log*	g_cDGELog;		// for DGE debugging. but you can it in your works.


protected:
	int		m_iWayOfLog;
	FILE*	m_FILE_log;

public:
	CDGE_Log();
	virtual ~CDGE_Log();

	void Out(const char *szFormat, ...);
	void SetWay(int iWay);

protected:
	void OpenLogFile();
	void CloseLogFile();
};



int		  CDGE_Log::g_cDGELogEnable = 0;
IDGE_Log* CDGE_Log::g_cDGELog = NULL;


void DGE_LogSetSate(int v)
{
	CDGE_Log::g_cDGELogEnable = v;
}


int	DGE_LogGetState()
{
	return CDGE_Log::g_cDGELogEnable;
}


IDGE_Log* DGE_Log()
{
	if(NULL == CDGE_Log::g_cDGELog)
		CDGE_Log::g_cDGELog = new CDGE_Log;


	return CDGE_Log::g_cDGELog;
}








CDGE_Log::CDGE_Log()
{
	m_iWayOfLog = DGE_LOG_WAY_SERIAL;

	m_FILE_log = NULL;
}


/*------------------------------------------------------------------------------
 Function Name :: ~CDGE_Log
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: Destructor
------------------------------------------------------------------------------*/
CDGE_Log::~CDGE_Log()
{
	CloseLogFile();
}


/*------------------------------------------------------------------------------
 Function Name :: OpenLogFile
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: open log file.
------------------------------------------------------------------------------*/
void CDGE_Log::OpenLogFile()
{
	if(DGE_LOG_WAY_NO == m_iWayOfLog)
		return;

	// "ab" 설정 시 도스 창 출력 파일 출력 혼합 사용 가능
	// 실행시 마다 로그 파일 구분 필요시 이전 파일 삭제( 편집 ) 과정 필요
	m_FILE_log = fopen("dge_log.txt", "wb");
}


/*------------------------------------------------------------------------------
 Function Name :: CloseLogFile
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: close log file.
------------------------------------------------------------------------------*/
void CDGE_Log::CloseLogFile()
{
	if(NULL != m_FILE_log)
	{
		fclose(m_FILE_log);
		m_FILE_log = NULL;
	}
}


/*------------------------------------------------------------------------------
 Function Name :: SetWay
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: change to way of log.
------------------------------------------------------------------------------*/
void CDGE_Log::SetWay(int iWay)
{
	m_iWayOfLog = iWay;

	// close log file.
	CloseLogFile();

	if(DGE_LOG_WAY_NO == m_iWayOfLog)
	{
	}
	else if(DGE_LOG_WAY_SERIAL == m_iWayOfLog)
	{
	}
	else if(DGE_LOG_WAY_FILE == m_iWayOfLog)
	{
		OpenLogFile();
	}
	else
	{
		// set to serial.
		m_iWayOfLog = DGE_LOG_WAY_SERIAL;
	}
}


/*------------------------------------------------------------------------------
 Function Name :: Out
 Return type   :: ...
 Return value  :: ...
 Input Value   :: ...
 Description   :: print string through serial port.
------------------------------------------------------------------------------*/
void CDGE_Log::Out(const char *szFormat, ...)
{
	char	szString[0xFF];
	va_list	argp;

	if(DGE_LOG_WAY_NO == m_iWayOfLog)
		return;

	memset(szString, 0, 0xFF);

	// 문장 만들기
	va_start(argp, szFormat);
	vsprintf(szString, szFormat, argp);
	va_end(argp);

	if(DGE_LOG_WAY_SERIAL == m_iWayOfLog)
	{
		printf(szString);
	}
	else
	{
		if(NULL != m_FILE_log)
		{
			fwrite(szString, sizeof(char), strlen(szString), m_FILE_log);
		}
		else
		{
			printf("DGE_Log :: can't write log to files.\r\n");
			printf(szString);
		}
	}
}
