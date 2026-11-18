short recv_data( int fComPort, unsigned char *pData, unsigned short nMaxLen ){

 short nResultLen = 0;

 nResultLen = read( fComPort, pData, nMaxLen );
 return nResultLen;
}