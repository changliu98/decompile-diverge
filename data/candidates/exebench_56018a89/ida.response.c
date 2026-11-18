void __cdecl util_word_to_dec(char *dst, unsigned int w)
{
  int v2; // eax
  int v3; // eax
  char v4; // cl
  char *v5; // rax
  bool v6; // [rsp+1h] [rbp-21h]
  int i; // [rsp+2h] [rbp-20h]
  int ia; // [rsp+2h] [rbp-20h]
  int ib; // [rsp+2h] [rbp-20h]
  int digval; // [rsp+6h] [rbp-1Ch]
  char dig_array[11]; // [rsp+Bh] [rbp-17h]
  unsigned int wa; // [rsp+16h] [rbp-Ch]
  char *dsta; // [rsp+1Ah] [rbp-8h]

  dsta = dst;
  wa = w;
  for ( i = 0; i < 10; ++i )
    dig_array[i] = 48;
  dig_array[10] = 0;
  ia = 9;
  while ( wa )
  {
    digval = wa % 0xA;
    wa /= 0xAu;
    v2 = ia--;
    dig_array[v2] = digval + 48;
  }
  for ( ib = 0; ; ++ib )
  {
    v6 = 0;
    if ( dig_array[ib] == 48 )
      v6 = ib < 9;
    if ( !v6 )
      break;
  }
  while ( dig_array[ib] )
  {
    v3 = ib++;
    v4 = dig_array[v3];
    v5 = dsta++;
    *v5 = v4;
  }
  *dsta = 0;
}