// Swaps the values of two integers.
void __cdecl std::swap<int>(int *p, int *q)
{
  int tmp = *p;
  *p = *q;
  *q = tmp;
}