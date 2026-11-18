int __cdecl foo(int *p1, int *p2)
{
  int v2; // eax
  int v3; // ecx

  v2 = (*p1)++;
  v3 = (*p2)++;
  return v3 + v2;
}