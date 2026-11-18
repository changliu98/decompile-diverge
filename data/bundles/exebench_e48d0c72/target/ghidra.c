int setLoopIters(double tMin,double tScale,double threshold_hi,uint *NLOOP)

{
  double dVar1;
  double timeMin;
  uint *NLOOP_local;
  double threshold_hi_local;
  double tScale_local;
  double tMin_local;
  
  dVar1 = tMin * tScale * (double)*NLOOP;
  if ((threshold_hi < dVar1) &&
     (*NLOOP = (uint)(long)(((double)*NLOOP * threshold_hi) / dVar1), *NLOOP < 2)) {
    *NLOOP = 2;
  }
  return 0;
}