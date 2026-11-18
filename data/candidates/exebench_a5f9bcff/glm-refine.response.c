int __cdecl foo(int *p1, int *p2)
{
  int val1 = (*p1)++;
  int val2 = (*p2)++;
  
  return val1 + val2;
}