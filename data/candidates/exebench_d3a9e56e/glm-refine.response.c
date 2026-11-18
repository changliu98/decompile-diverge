void __cdecl reverseInt(int *p)
{
  for (int i = 0; i < 5; ++i)
  {
    int temp = p[i];
    p[i] = p[9 - i];
    p[9 - i] = temp;
  }
}