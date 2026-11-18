void __cdecl reorder(int *a, int *b)
{
  int t; // [rsp+0h] [rbp-14h]

  if ( *a > *b )
  {
    t = *a;
    *a = *b;
    *b = t;
  }
}