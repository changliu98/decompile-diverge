short __cdecl recv_data(int fComPort, unsigned __int8 *pData, unsigned __int16 nMaxLen)
{
  return read(fComPort, pData, nMaxLen);
}