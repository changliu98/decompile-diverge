/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float nabs_sf(float *p)

{
  float f;
  float *p_local;
  
  return -(float)((uint)*p & _DAT_00102010);
}