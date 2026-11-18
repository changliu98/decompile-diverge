int __cdecl func0(__int64 num1, __int64 num2)
{
  int count; // [rsp+0h] [rbp-1Ch]
  __int64 number; // [rsp+4h] [rbp-18h]

  number = num2 + num1;
  count = 0;
  while ( number > 0 )
  {
    number /= 10LL;
    ++count;
  }
  return count;
}