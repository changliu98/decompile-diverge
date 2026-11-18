char *__cdecl ikcp_encode8u(char *p, unsigned __int8 c)
{
  *p = c;
  return p + 1;
}