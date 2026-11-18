char * base91(char *p,int i)

{
  int i_local;
  char *p_local;
  
  *p = (char)(i / 0x5b) + '!';
  p[1] = (char)(i % 0x5b) + '!';
  return p + 2;
}