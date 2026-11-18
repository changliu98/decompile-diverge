void __cdecl swap_ptr(long *a, long *b)
{
  long tmp = *a;
  *a = *b;
  *b = tmp;
}