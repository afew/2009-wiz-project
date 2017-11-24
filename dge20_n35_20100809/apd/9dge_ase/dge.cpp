// Start Program.
//
////////////////////////////////////////////////////////////////////////////////


#include "_StdAfx.h"


CMain*	g_pApp = NULL;


int main(int argc, char* argv[])
{
	int		hr=0;

	CMain	mainApp;
	g_pApp = &mainApp;

	hr = mainApp.Create();
	if(DGE_FAILED(hr))
		return DGE_OK;

	hr = mainApp.Run();

	return hr;
}



