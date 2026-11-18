void clip_coord(int *coord,int min,int max)

{
  int local_24;
  int local_20;
  int tmp;
  int max_local;
  int min_local;
  int *coord_local;
  
  local_20 = *coord;
  if (local_20 < min) {
    local_20 = min;
  }
  local_24 = max;
  if (local_20 <= max) {
    local_24 = local_20;
  }
  *coord = local_24;
  return;
}