void __cdecl swap(int *p)
{
  int *pmin; // [rsp+0h] [rbp-28h]
  int *pmina; // [rsp+0h] [rbp-28h]
  int *pminb; // [rsp+0h] [rbp-28h]
  int *pminc; // [rsp+0h] [rbp-28h]
  int *pmax; // [rsp+8h] [rbp-20h]
  int temp; // [rsp+14h] [rbp-14h]
  int tempa; // [rsp+14h] [rbp-14h]
  int tempb; // [rsp+14h] [rbp-14h]
  int tempc; // [rsp+14h] [rbp-14h]
  int j; // [rsp+18h] [rbp-10h]
  int ja; // [rsp+18h] [rbp-10h]
  int jb; // [rsp+18h] [rbp-10h]
  int jc; // [rsp+18h] [rbp-10h]
  int i; // [rsp+1Ch] [rbp-Ch]
  int ia; // [rsp+1Ch] [rbp-Ch]
  int ib; // [rsp+1Ch] [rbp-Ch]
  int ic; // [rsp+1Ch] [rbp-Ch]

  pmax = p;
  pmin = p;
  for ( i = 0; i < 5; ++i )
  {
    for ( j = i; j < 5; ++j )
    {
      if ( *pmax < p[5 * i + j] )
        pmax = &p[5 * i + j];
      if ( *pmin > p[5 * i + j] )
        pmin = &p[5 * i + j];
    }
  }
  temp = p[12];
  p[12] = *pmax;
  *pmax = temp;
  *pmin = *pmin;
  pmina = p + 1;
  for ( ia = 0; ia < 5; ++ia )
  {
    for ( ja = 0; ja < 5; ++ja )
    {
      if ( (ia || ja) && *pmina > p[5 * ia + ja] )
        pmina = &p[5 * ia + ja];
    }
  }
  tempa = *pmina;
  *pmina = p[4];
  p[4] = tempa;
  pminb = p + 1;
  for ( ib = 0; ib < 5; ++ib )
  {
    for ( jb = 0; jb < 5; ++jb )
    {
      if ( (ib || jb) && (ib || jb != 4) && *pminb > p[5 * ib + jb] )
        pminb = &p[5 * ib + jb];
    }
  }
  tempb = *pminb;
  *pminb = p[20];
  p[20] = tempb;
  pminc = p + 1;
  for ( ic = 0; ic < 5; ++ic )
  {
    for ( jc = 0; jc < 5; ++jc )
    {
      if ( (ic || jc) && (ic || jc != 4) && (ic != 4 || jc) && *pminc > p[5 * ic + jc] )
        pminc = &p[5 * ic + jc];
    }
  }
  tempc = *pminc;
  *pminc = p[24];
  p[24] = tempc;
}