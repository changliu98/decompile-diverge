char * ikcp_encode8u(char *p,uchar c)

{
  uchar c_local;
  char *p_local;
  
  *p = c;
  return p + 1;
}