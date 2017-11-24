//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __Util_H__
#define __Util_H__

int SaveFile( char *fn, long *buff, long size );
int LoadFile( char *fn, long *buff, long size );
long GetConfig( char* fn, char* cParam );
long LogFileWrite( char* fn, char* cParam );

long funcSin( long rdo );
long funcCos( long rdo );
long funcTan2( long posX, long posY );


#endif


