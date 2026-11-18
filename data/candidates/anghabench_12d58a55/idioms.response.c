char *ikcp_encode8u(char *s, char c)
{
  *s = c;
  return s + 1;
}