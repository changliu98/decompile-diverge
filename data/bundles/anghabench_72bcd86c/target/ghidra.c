float LerpAngle(float from,float to,float frac)

{
  float a;
  float frac_local;
  float to_local;
  float from_local;
  
  to_local = to;
  if (DAT_00102004 < to - from) {
    to_local = to - DAT_00102008;
  }
  if (to_local - from < DAT_0010200c) {
    to_local = DAT_00102008 + to_local;
  }
  return frac * (to_local - from) + from;
}