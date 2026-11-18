void __cdecl sort4_sorting_network_simple_swap(short *d)
{
  short v1; // [rsp+0h] [rbp-44h]
  short v2; // [rsp+4h] [rbp-40h]
  short v3; // [rsp+8h] [rbp-3Ch]
  short v4; // [rsp+Ch] [rbp-38h]
  short v5; // [rsp+10h] [rbp-34h]
  short v6; // [rsp+14h] [rbp-30h]
  short v7; // [rsp+18h] [rbp-2Ch]
  short v8; // [rsp+1Ch] [rbp-28h]
  short v9; // [rsp+20h] [rbp-24h]
  short v10; // [rsp+24h] [rbp-20h]

  if ( *d >= d[1] )
    v10 = d[1];
  else
    v10 = *d;
  if ( *d >= d[1] )
    v9 = *d;
  else
    v9 = d[1];
  *d = v10;
  d[1] = v9;
  if ( d[2] >= d[3] )
    v8 = d[3];
  else
    v8 = d[2];
  if ( d[2] >= d[3] )
    v7 = d[2];
  else
    v7 = d[3];
  d[2] = v8;
  d[3] = v7;
  if ( *d >= d[2] )
    v6 = d[2];
  else
    v6 = *d;
  if ( *d >= d[2] )
    v5 = *d;
  else
    v5 = d[2];
  *d = v6;
  d[2] = v5;
  if ( d[1] >= d[3] )
    v4 = d[3];
  else
    v4 = d[1];
  if ( d[1] >= d[3] )
    v3 = d[1];
  else
    v3 = d[3];
  d[1] = v4;
  d[3] = v3;
  if ( d[1] >= d[2] )
    v2 = d[2];
  else
    v2 = d[1];
  if ( d[1] >= d[2] )
    v1 = d[1];
  else
    v1 = d[2];
  d[1] = v2;
  d[2] = v1;
}