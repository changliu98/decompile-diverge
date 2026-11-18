char *ikcp_encode8u(char *p, unsigned char c)
{
  *p = (char)c;
  return p + 1;
}