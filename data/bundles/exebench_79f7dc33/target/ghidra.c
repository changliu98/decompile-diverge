void bToHex0(char *pWrite,uchar ch)

{
  char *digits;
  uchar ch_local;
  char *pWrite_local;
  
  *pWrite = "0123456789abcdef"[(int)(uint)ch >> 4];
  pWrite[1] = "0123456789abcdef"[(int)(ch & 0xf)];
  pWrite[2] = '\0';
  return;
}