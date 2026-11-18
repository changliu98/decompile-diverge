void __cdecl sum(int n1, int d1, int n2, int d2, int *r1, int *r2)
{
  *r1 = d1 * n2 + d2 * n1;
  *r2 = d2 * d1;
}