char * byte2bin(char in,char *out)

{
  char cVar1;
  int n;
  char *out_local;
  char in_local;
  
  for (n = 0; n < 8; n = n + 1) {
    cVar1 = '1';
    if (((int)in & 1 << (7U - (char)n & 0x1f)) == 0) {
      cVar1 = '0';
    }
    out[n] = cVar1;
  }
  out[8] = '\0';
  return out;
}