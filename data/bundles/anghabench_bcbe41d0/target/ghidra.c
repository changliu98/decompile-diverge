float constrain(float min,float max,float a)

{
  float a_local;
  float max_local;
  float min_local;
  float local_c;
  
  local_c = min;
  if ((min <= a) && (local_c = a, max < a)) {
    local_c = max;
  }
  return local_c;
}