void wordstore(char *p,int w)

{
  int w_local;
  char *p_local;
  
  *p = (char)w;
  p[1] = (char)((uint)w >> 8);
  return;
}