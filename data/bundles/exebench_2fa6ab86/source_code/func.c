#include <stdio.h>

#include <fcntl.h>  

#include <sys/types.h> 

#include <sys/select.h> 

#include <netdb.h> 

#include <string.h> 

#include <errno.h> 

#include <unistd.h>  

short recv_data( int fComPort, unsigned char *pData, unsigned short nMaxLen ){

 short nResultLen = 0;

 nResultLen = read( fComPort, pData, nMaxLen );
 return nResultLen;
}
