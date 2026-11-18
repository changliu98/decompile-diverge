int __cdecl func0(int a, int b)
{
  int temp;
  while (b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return a;
}