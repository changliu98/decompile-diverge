int __cdecl putdword(char *p, int w)
{
  *(_WORD *)p = w;
  return w;
}