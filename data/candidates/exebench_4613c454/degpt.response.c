void cquat_scale(double *qdest,double c,double *qorg)

{
  double *qorg_local;
  double c_local;
  double *qdest_local;
  
  *qdest = c * *qorg;
  qdest[1] = c * qorg[1];
  qdest[2] = c * qorg[2];
  qdest[3] = c * qorg[3];
  return;
}