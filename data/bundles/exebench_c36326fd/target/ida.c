void __cdecl initialize_temp(unsigned int *a, unsigned int *t)
{
  int v2; // ecx
  int j; // [rsp+0h] [rbp-18h]
  int i; // [rsp+4h] [rbp-14h]

  i = 9;
  j = 14;
  while ( i >= 0 )
    t[j--] = a[i--];
  while ( j != -1 )
  {
    v2 = j--;
    t[v2] = 0;
  }
}