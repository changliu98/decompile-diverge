int Serial_WriteData(int portId,uchar *data,int length)

{
  ssize_t sVar1;
  int length_local;
  uchar *data_local;
  int portId_local;
  
  sVar1 = write(portId,data,(long)length);
  return (int)sVar1;
}