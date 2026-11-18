void __cdecl max_ptr(int *p, int *q)
{
  if (*p > *q)
  {
    // Swap the values of *p and *q
    int temp = *p;
    *p = *q;
    *q = temp;
  }
}