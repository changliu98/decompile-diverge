void mlCubicBezier(float *p0,float *p1,float *p2,float *p3,float t,float *v)

{
  float *v_local;
  float t_local;
  float *p3_local;
  float *p2_local;
  float *p1_local;
  float *p0_local;
  
  *v = t * t * t * *p3 +
       DAT_00102004 * (DAT_00102008 - t) * t * t * *p2 +
       (DAT_00102008 - t) * (DAT_00102008 - t) * (DAT_00102008 - t) * *p0 +
       DAT_00102004 * (DAT_00102008 - t) * (DAT_00102008 - t) * t * *p1;
  v[1] = t * t * t * p3[1] +
         DAT_00102004 * (DAT_00102008 - t) * t * t * p2[1] +
         (DAT_00102008 - t) * (DAT_00102008 - t) * (DAT_00102008 - t) * p0[1] +
         DAT_00102004 * (DAT_00102008 - t) * (DAT_00102008 - t) * t * p1[1];
  v[2] = t * t * t * p3[2] +
         DAT_00102004 * (DAT_00102008 - t) * t * t * p2[2] +
         (DAT_00102008 - t) * (DAT_00102008 - t) * (DAT_00102008 - t) * p0[2] +
         DAT_00102004 * (DAT_00102008 - t) * (DAT_00102008 - t) * t * p1[2];
  return;
}