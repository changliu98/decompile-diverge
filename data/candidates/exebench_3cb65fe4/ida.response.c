char *__cdecl get_begin(char *nbr, int *sg)
{
  bool v3; // [rsp+1h] [rbp-19h]
  int sign; // [rsp+2h] [rbp-18h]
  int lp; // [rsp+6h] [rbp-14h]

  lp = 0;
  sign = 1;
  while ( 1 )
  {
    v3 = 1;
    if ( nbr[lp] != 43 )
      v3 = nbr[lp] == 45;
    if ( !v3 )
      break;
    if ( nbr[lp] == 45 )
      sign = -sign;
    ++lp;
  }
  *sg = sign;
  return &nbr[lp];
}