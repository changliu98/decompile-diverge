int __cdecl genx(unsigned __int8 *dst, unsigned __int8 *field)
{
  int result; // eax
  int i; // [rsp+8h] [rbp-224h]
  int ia; // [rsp+8h] [rbp-224h]
  int ib; // [rsp+8h] [rbp-224h]
  short index[256]; // [rsp+Ch] [rbp-220h]
  int error; // [rsp+218h] [rbp-14h]
  unsigned __int8 *fielda; // [rsp+21Ch] [rbp-10h]
  unsigned __int8 *dsta; // [rsp+224h] [rbp-8h]

  dsta = dst;
  fielda = field;
  error = 0;
  for ( i = 0; i < 256; ++i )
    index[i] = -1;
  for ( ia = 0; ia < 256; ++ia )
  {
    if ( index[fielda[ia]] == -1 )
      index[fielda[ia]] = ia;
    else
      error = 1;
  }
  for ( ib = 0; ib < 256; ++ib )
    dsta[ib] = index[ib];
  result = -1;
  if ( !error )
    return 0;
  return result;
}