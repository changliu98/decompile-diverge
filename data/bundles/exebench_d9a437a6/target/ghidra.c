unsigned_long do_csum(uchar *buff,int len,unsigned_long result)

{
  unsigned_long result_local;
  int len_local;
  uchar *buff_local;
  
  result_local = result;
  if (((ulong)buff & 2) != 0) {
    result_local = result + 1;
  }
  return result_local;
}