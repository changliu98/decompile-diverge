returns 101
int __cdecl func0(int N)
{
  int B_Number = 0;
  int power_of_10 = 1;

  while (N)
  {
    B_Number += power_of_10 * (N % 2);
    N /= 2;
    power_of_10 *= 10;
  }

  return B_Number;
}