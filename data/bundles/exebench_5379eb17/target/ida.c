void __cdecl max_ptr(int *p, int *q)
{
  if ( *p > *q )
  {
    *p ^= *q;
    *q ^= *p;
    *p ^= *q;
  }
}