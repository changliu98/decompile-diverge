void ComputeAndOrientation(float heading,float *euler,float *result)

{
  float roll;
  float pitch;
  float *result_local;
  float *euler_local;
  float heading_local;
  
  *result = heading;
  pitch = *euler;
  roll = euler[1];
  if (pitch < 0.0) {
    pitch = DAT_00102004 + pitch;
  }
  if (roll < 0.0) {
    roll = DAT_00102004 + roll;
  }
  if (((DAT_00102008 < roll) && (roll < DAT_0010200c)) &&
     (pitch = pitch - DAT_00102010, pitch < 0.0)) {
    pitch = DAT_00102004 + pitch;
  }
  if (pitch <= DAT_00102010) {
    result[1] = -pitch;
  }
  if (DAT_00102010 < pitch) {
    result[1] = DAT_00102004 - pitch;
  }
  if ((roll < 0.0) || (DAT_00102008 < roll)) {
    if ((roll <= DAT_00102008) || (DAT_0010200c <= roll)) {
      result[2] = roll - DAT_00102004;
    }
    else {
      result[2] = DAT_00102010 - roll;
    }
  }
  else {
    result[2] = roll;
  }
  return;
}