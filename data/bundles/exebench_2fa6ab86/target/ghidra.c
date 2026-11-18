short recv_data(int fComPort,uchar *pData,unsigned_short nMaxLen)

{
  ssize_t sVar1;
  short nResultLen;
  unsigned_short nMaxLen_local;
  uchar *pData_local;
  int fComPort_local;
  
  sVar1 = read(fComPort,pData,(ulong)nMaxLen);
  return (short)sVar1;
}