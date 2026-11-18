int __cdecl func0(int l1, int r1, int l2, int r2, int *x, int *y)
{
  int v7; // [rsp+0h] [rbp-30h]
  int v8; // [rsp+4h] [rbp-2Ch]
  int v9; // [rsp+8h] [rbp-28h]
  int v10; // [rsp+Ch] [rbp-24h]

  if ( l1 == l2 )
  {
    v9 = -1;
  }
  else
  {
    if ( l1 >= l2 )
      v10 = l2;
    else
      v10 = l1;
    v9 = v10;
  }
  *x = v9;
  if ( r1 == r2 )
  {
    v7 = -1;
  }
  else
  {
    if ( r1 <= r2 )
      v8 = r2;
    else
      v8 = r1;
    v7 = v8;
  }
  *y = v7;
  return 0;
}