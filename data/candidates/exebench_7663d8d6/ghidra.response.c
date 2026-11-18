void treemove(double *bb,double s,int d)

{
  int d_local;
  double s_local;
  double *bb_local;
  
  if ((d & 1U) == 0) {
    bb[3] = bb[3] - s;
  }
  else {
    *bb = s + *bb;
  }
  if ((d & 2U) == 0) {
    bb[4] = bb[4] - s;
  }
  else {
    bb[1] = s + bb[1];
  }
  if ((d & 4U) == 0) {
    bb[5] = bb[5] - s;
  }
  else {
    bb[2] = s + bb[2];
  }
  return;
}