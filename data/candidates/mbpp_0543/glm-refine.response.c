int __cdecl func0(__int64 num1, __int64 num2)
{
  int count = 0;
  for (__int64 number = num1 + num2; number > 0; number /= 10)
    ++count;
  return count;
}