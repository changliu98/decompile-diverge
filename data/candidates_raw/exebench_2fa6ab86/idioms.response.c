int readCom(int fComPort, void *pData, unsigned short nMaxLen)
{
  int nRead = read(fComPort, pData, nMaxLen);
  return nRead;
}