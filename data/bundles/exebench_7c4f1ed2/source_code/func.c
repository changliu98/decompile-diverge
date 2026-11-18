#include <fcntl.h>

#include <stdlib.h>

#include <string.h>

#include <sys/socket.h>

#include <sys/types.h>

#include <unistd.h>

void decode_dir(short d,int*x,int*y){
*x=(d&0xFF)-2;
*y=((d&0xFF00)>>8)-2;
}
