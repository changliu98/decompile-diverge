int __cdecl foo(int *a)
{
  int j = 0;
  int i = 0;

  for (; i < 10; ++i)
  {
    a[i] = j++;
  }
  
  return j + i;
}