int __cdecl g(int *p, short *q)
{
  int x; // [rsp+0h] [rbp-14h]

  x = *q;
  *p = 10;
  return x;
}