/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int func0(char *value)

{
  double dVar1;
  undefined8 local_20;
  double w;
  char *value_local;
  
  dVar1 = atof(value);
  if (0.0 <= dVar1) {
    local_20 = floor(_DAT_00102008 + dVar1);
  }
  else {
    local_20 = ceil(dVar1 - _DAT_00102008);
  }
  return (int)local_20;
}