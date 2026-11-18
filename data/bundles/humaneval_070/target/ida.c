void __cdecl func0(int *lst, int size, int *out)
{
  int v3; // ecx
  int v4; // edx
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  int index; // [rsp+0h] [rbp-30h]
  int r; // [rsp+4h] [rbp-2Ch]
  int l; // [rsp+8h] [rbp-28h]
  int temp; // [rsp+Ch] [rbp-24h]
  int j; // [rsp+10h] [rbp-20h]
  int i; // [rsp+14h] [rbp-1Ch]

  for ( i = 0; i < size - 1; ++i )
  {
    for ( j = i + 1; j < size; ++j )
    {
      if ( lst[i] > lst[j] )
      {
        temp = lst[i];
        lst[i] = lst[j];
        lst[j] = temp;
      }
    }
  }
  l = 0;
  r = size - 1;
  index = 0;
  while ( l <= r )
  {
    v3 = l;
    if ( l == r )
    {
      ++l;
    }
    else
    {
      ++l;
      v6 = lst[v3];
      v7 = index++;
      out[v7] = v6;
      v3 = r--;
    }
    v4 = lst[v3];
    v5 = index++;
    out[v5] = v4;
  }
}