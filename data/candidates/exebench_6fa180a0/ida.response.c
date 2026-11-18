void __cdecl sortVrtx(int *vrt)
{
  int o; // [rsp+0h] [rbp-14h]
  int tmp; // [rsp+4h] [rbp-10h]
  int i; // [rsp+8h] [rbp-Ch]

  do
  {
    o = 1;
    for ( i = 1; i < 3; ++i )
    {
      if ( vrt[i - 1] > vrt[i] )
      {
        tmp = vrt[i];
        vrt[i] = vrt[i - 1];
        vrt[i - 1] = tmp;
        o = 0;
      }
    }
  }
  while ( !o );
}