void update16(uint16_t *target,int max,int intensity,int limit)

{
  int limit_local;
  int intensity_local;
  int max_local;
  uint16_t *target_local;
  
  if (max < (int)(uint)*target) {
    *target = (uint16_t)limit;
  }
  else {
    *target = *target + (short)intensity;
  }
  return;
}