int __cdecl func0(int n)
{
  int count; // [rsp+0h] [rbp-8h]

  count = 0;
  while ( n )
  {
    n /= 10;
    ++count;
  }
  return count;
}