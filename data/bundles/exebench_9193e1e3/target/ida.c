void __cdecl clip_coord(int *coord, int min, int max)
{
  int v3; // [rsp+0h] [rbp-1Ch]
  int v4; // [rsp+4h] [rbp-18h]

  if ( *coord >= min )
    v4 = *coord;
  else
    v4 = min;
  if ( v4 <= max )
    v3 = v4;
  else
    v3 = max;
  *coord = v3;
}