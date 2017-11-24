

#if defined(_WIN32) || defined(WIN32)
#pragma comment(lib, "DGT_Util_.lib")
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <DGE_Type.h>
#include <DGT_Lzo.h>


#define MEDIA_DIR	"../../media/"


int main(int argc, char* argv[])
{
	// Lzo 초기화
	if(DGE_FAILED(DgtLzo_Init()))
		return 0;

//	char	sSrc[260]="bg.png";
	char	sSrc[260]=MEDIA_DIR"page_03.lua";
	char	sDst[260]=MEDIA_DIR"t.gpz";

	// 압축
	if(DGE_FAILED(DgtLzo_CompressFile(sDst, sSrc)))
		return -1;

	// 압축 파일을 특정 폴더에 풀기
	if(DGE_FAILED(DgtLzo_DeCompressFile("../", "t.gpz")))
		return -1;


	unsigned char* sbuf;
	unsigned long  lbuf;

	// 압축 파일에서 데이터 직접 가져오기
	if(DGE_FAILED(DgtLzo_DeCompressFromFile(&sbuf, &lbuf, "t.gpz")))
		return -1;


	// Debugging...
	FILE* fp = fopen("tt.txt", "wt");
	fwrite(sbuf, sizeof(unsigned char), lbuf, fp);
	free(sbuf);
	fclose(fp);

	char sLine[512];
	fp = fopen("tt.txt", "rt");

	while(!feof(fp))
	{
		fgets(sLine, 512, fp);
		printf("%s", sLine);
	}

	fclose(fp);

	DgtLzo_Close();


	return 0;
}


