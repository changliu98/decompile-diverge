void dwordstore(char *p,int d)

{
  int d_local;
  char *p_local;
  
  *p = (char)d;
  p[1] = (char)((uint)d >> 8);
  p[2] = (char)((uint)d >> 0x10);
  p[3] = (char)((uint)d >> 0x18);
  return;
}