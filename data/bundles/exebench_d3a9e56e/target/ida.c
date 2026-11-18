void __cdecl reverseInt(int *p)
{
  int temp; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  for ( i = 0; i < 5; ++i )
  {
    temp = p[i];
    p[i] = p[10 - i - 1];
    p[10 - i - 1] = temp;
  }
}