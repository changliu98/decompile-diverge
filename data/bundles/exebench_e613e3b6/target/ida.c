int __cdecl cal_intervals(int *stalls, int *intervals, int num)
{
  bool v4; // [rsp+1h] [rbp-23h]
  bool v5; // [rsp+2h] [rbp-22h]
  bool v6; // [rsp+3h] [rbp-21h]
  int i; // [rsp+4h] [rbp-20h]
  int inter; // [rsp+8h] [rbp-1Ch]
  int segs; // [rsp+Ch] [rbp-18h]

  segs = 0;
  for ( i = 0; ; ++i )
  {
    v6 = 0;
    if ( i < num )
      v6 = stalls[i] == 0;
    if ( !v6 )
      break;
  }
  while ( i < num )
  {
    while ( 1 )
    {
      v5 = 0;
      if ( i < num )
        v5 = stalls[i] != 0;
      if ( !v5 )
        break;
      ++i;
    }
    for ( inter = 0; ; ++inter )
    {
      v4 = 0;
      if ( i < num )
        v4 = stalls[i] == 0;
      if ( !v4 )
        break;
      ++i;
    }
    if ( i < num )
      intervals[segs++] = inter;
  }
  return segs + 1;
}