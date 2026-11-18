void OsdGetBSplineWeights(float t,float *wP,float *wDP,float *wDP2)

{
  float fVar1;
  float fVar2;
  float t3;
  float t2;
  float one6th;
  float *wDP2_local;
  float *wDP_local;
  float *wP_local;
  float t_local;
  
  fVar1 = t * t;
  fVar2 = t * fVar1;
  *wP = DAT_00102020 * (((t - fVar1) * DAT_00102034 + DAT_00102028) - fVar2);
  wP[1] = DAT_00102020 * (fVar2 * DAT_00102024 + fVar1 * DAT_0010202c + DAT_00102030);
  wP[2] = DAT_00102020 * (((t + fVar1) - fVar2) * DAT_00102024 + DAT_00102028);
  wP[3] = DAT_00102020 * fVar2;
  if (wDP != (float *)0x0) {
    *wDP = (fVar1 * DAT_00102048 + t) - DAT_00102038;
    wDP[1] = fVar1 * DAT_00102040 + -(DAT_00102044 * t);
    wDP[2] = fVar1 * DAT_0010203c + t + DAT_00102038;
    wDP[3] = DAT_00102038 * fVar1;
  }
  if (wDP2 != (float *)0x0) {
    *wDP2 = -t + DAT_00102028;
    wDP2[1] = t * DAT_00102024 + DAT_0010204c;
    wDP2[2] = t * DAT_00102034 + DAT_00102028;
    wDP2[3] = t;
  }
  return;
}