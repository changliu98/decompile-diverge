int __cdecl func0(int n1, int n2)
{
  int sum; // [rsp+0h] [rbp-10h]
  int distance; // [rsp+4h] [rbp-Ch]

  distance = abs(n1 - n2);
  sum = 0;
  while ( distance > 0 )
  {
    sum += distance % 10;
    distance /= 10;
  }
  return sum;
}