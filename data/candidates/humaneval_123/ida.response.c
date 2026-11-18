void __cdecl func0(int n, int *out, int *size)
{
  int v3; // ecx
  bool v4; // [rsp+7h] [rbp-29h]
  int j; // [rsp+8h] [rbp-28h]
  int key; // [rsp+Ch] [rbp-24h]
  int i; // [rsp+10h] [rbp-20h]
  int capacity; // [rsp+14h] [rbp-1Ch]
  int *outa; // [rsp+20h] [rbp-10h]

  outa = out;
  capacity = 10;
  *size = 1;
  *out = 1;
  while ( n != 1 )
  {
    if ( n % 2 == 1 )
    {
      if ( *size >= capacity )
      {
        capacity *= 2;
        outa = (int *)realloc(outa, 4LL * capacity);
      }
      v3 = (*size)++;
      outa[v3] = n;
      n = 3 * n + 1;
    }
    else
    {
      n /= 2;
    }
  }
  for ( i = 1; i < *size; ++i )
  {
    key = outa[i];
    for ( j = i - 1; ; --j )
    {
      v4 = 0;
      if ( j >= 0 )
        v4 = outa[j] > key;
      if ( !v4 )
        break;
      outa[j + 1] = outa[j];
    }
    outa[j + 1] = key;
  }
}