int sendbytes(int port,uchar *data,int len)

{
  int len_local;
  uchar *data_local;
  int port_local;
  
  write(port,data,(ulong)(uint)len);
  return 0;
}