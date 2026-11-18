int __cdecl par_msquares_multi_code(int sw, int se, int ne, int nw)
{
  int v4; // eax
  int ncols; // [rsp+0h] [rbp-24h]
  int code_4; // [rsp+8h] [rbp-1Ch]
  int code_8; // [rsp+Ch] [rbp-18h]
  int code_12; // [rsp+10h] [rbp-14h]

  ncols = 1;
  if ( se == sw )
  {
    code_4 = 0;
  }
  else
  {
    ncols = 2;
    code_4 = 1;
  }
  if ( ne == se )
  {
    code_8 = code_4;
  }
  else if ( ne == sw )
  {
    code_8 = 0;
  }
  else
  {
    v4 = ncols++;
    code_8 = v4;
  }
  if ( nw == ne )
  {
    code_12 = code_8;
  }
  else if ( nw == se )
  {
    code_12 = code_4;
  }
  else if ( nw == sw )
  {
    code_12 = 0;
  }
  else
  {
    code_12 = ncols;
  }
  return (code_12 << 6) | (16 * code_8) | (4 * code_4);
}