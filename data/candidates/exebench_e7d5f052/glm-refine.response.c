void __cdecl SJIStoJIS(int *p1, int *p2)
{
  unsigned __int8 c1 = (unsigned __int8)*p1;
  unsigned __int8 c2 = (unsigned __int8)*p2;
  
  int adjust1 = (c1 < 0xA0) ? 112 : 176;
  int adjust2;
  
  if (c2 >= 0x9F)
    adjust2 = 126;
  else
    adjust2 = 31 + (c2 > 0x7F);

  *p1 = 2 * (c1 - adjust1);
  *p2 = c2 - adjust2;
}