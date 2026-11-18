int __cdecl func0(int a, int b)
{
  int last_digit_a = abs(a) % 10;
  return last_digit_a * (abs(b) % 10);
}