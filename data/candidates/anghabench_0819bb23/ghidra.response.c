float clamp(float x,float min,float max)

{
  float max_local;
  float min_local;
  float x_local;
  float local_c;
  
  local_c = min;
  if ((min <= x) && (local_c = x, max < x)) {
    local_c = max;
  }
  return local_c;
}