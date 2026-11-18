void ComputeAndOrientation(float azimuth, float *elevation, float *orientation) {
  float az, el;
  orientation[0] = azimuth;
  az = elevation[0];
  el = elevation[1];
  if (az < 0) az += 360;
  if (el < 0) el += 360;
  if (el > 90 && el < 270) {
    az -= 180;
    if (az < 0) az += 360;
  }
  if (az <= 180)
    orientation[1] = -az;
  else
    orientation[1] = 360 - az;
  if (el >= 0 && el <= 90)
    orientation[2] = el;
  else if (el > 90 && el < 270)
    orientation[2] = 180 - el;
  else
    orientation[2] = el - 360;
}