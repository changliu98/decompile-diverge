void OsdGetBezierWeights(float t,float *wP,float *wDP,float *wDP2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float tC2;
  float tC;
  float t2;
  float *wDP2_local;
  float *wDP_local;
  float *wP_local;
  float t_local;
  
  fVar1 = t * t;
  fVar2 = DAT_00102024 - t;
  fVar3 = fVar2 * fVar2;
  *wP = fVar3 * fVar2;
  wP[1] = fVar3 * t * DAT_00102020;
  wP[2] = fVar1 * fVar2 * DAT_00102020;
  wP[3] = fVar1 * t;
  if (wDP != (float *)0x0) {
    *wDP = DAT_00102038 * fVar3;
    wDP[1] = fVar1 * DAT_00102030 + -(DAT_00102034 * t) + DAT_00102020;
    wDP[2] = fVar1 * DAT_00102028 + DAT_0010202c * t;
    wDP[3] = DAT_00102020 * fVar1;
  }
  if (wDP2 != (float *)0x0) {
    *wDP2 = DAT_0010202c * fVar2;
    wDP2[1] = t * DAT_00102040 + DAT_00102044;
    wDP2[2] = t * DAT_0010203c + DAT_0010202c;
    wDP2[3] = DAT_0010202c * t;
  }
  return;
}