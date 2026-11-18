char *__cdecl i2hs(unsigned int n, char *ds_0)
{
  char *v2; // rax
  char *v3; // rax
  char *v4; // rax
  char *v5; // rcx
  char *dsp; // [rsp+0h] [rbp-50h]
  char *tsp; // [rsp+8h] [rbp-48h]
  char ts[32]; // [rsp+10h] [rbp-40h] BYREF
  char *tb; // [rsp+38h] [rbp-18h]
  char *ds_0a; // [rsp+40h] [rbp-10h]
  unsigned int na; // [rsp+4Ch] [rbp-4h]

  na = n;
  ds_0a = ds_0;
  tb = "0123456789ABCDEF";
  tsp = ts;
  dsp = ds_0;
  ts[0] = 0;
  while ( na )
  {
    v2 = tsp++;
    v2[1] = tb[na & 0xF];
    na >>= 4;
  }
  if ( !*tsp )
  {
    v3 = tsp++;
    v3[1] = 48;
  }
  do
  {
    v4 = tsp--;
    LOBYTE(v4) = *v4;
    v5 = dsp++;
    *v5 = (char)v4;
  }
  while ( (_BYTE)v4 );
  return ds_0a;
}