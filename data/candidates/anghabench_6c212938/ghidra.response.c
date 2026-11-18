void copy_le16(uchar *dest,uint n)

{
  uint n_local;
  uchar *dest_local;
  
  *dest = (uchar)n;
  dest[1] = (uchar)(n >> 8);
  return;
}