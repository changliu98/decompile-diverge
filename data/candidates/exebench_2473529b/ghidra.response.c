void normalize_angle(double *angle)

{
  double *angle_local;
  
  while (DAT_00102008 < *angle) {
    *angle = *angle - DAT_00102008;
  }
  while (*angle <= 0.0 && *angle != 0.0) {
    *angle = DAT_00102008 + *angle;
  }
  return;
}