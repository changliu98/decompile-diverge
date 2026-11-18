int RS232Read(int fComPort, char *pcBuf, unsigned short usLen)
{
 int nResult = 0;

 nResult = read(fComPort, pcBuf, usLen);

 return nResult;
}