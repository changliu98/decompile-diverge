void __cdecl removeslave(int *slave, int n)
{
  int i; // [rsp+0h] [rbp-10h]

  for ( i = 9; i >= 0; --i )
  {
    if ( slave[i] )
    {
      slave[i] = 0;
      --n;
    }
    if ( !n )
      break;
  }
}