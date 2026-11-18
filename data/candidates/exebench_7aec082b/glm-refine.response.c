int __cdecl g(int *p, short *q)
{
  int x = *q;
  *p = 10;
  return x;
}