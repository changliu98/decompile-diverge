/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void measure(long *inches,int *inch,int *feet,int *yard,int *mile)

{
  int *mile_local;
  int *yard_local;
  int *feet_local;
  int *inch_local;
  long *inches_local;
  
  *inches = 0xf780;
  *inch = (int)*inches;
  *feet = (int)((double)*inches * _DAT_00102018);
  *yard = (int)((double)*inches * DAT_00102010);
  *mile = (int)((double)*inches * DAT_00102008);
  return;
}