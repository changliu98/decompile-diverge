void __cdecl clip_coord(int *coord, int min, int max)
{
  int v = (*coord >= min) ? *coord : min;
  *coord = (v <= max) ? v : max;
}