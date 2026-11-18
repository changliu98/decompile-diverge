int zmlt_(double *ar,double *ai,double *br,double *bi,double *cr,double *ci)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double cb;
  double ca;
  double *ci_local;
  double *cr_local;
  double *bi_local;
  double *br_local;
  double *ai_local;
  double *ar_local;
  
  dVar1 = *ar;
  dVar2 = *bi;
  dVar3 = *ai;
  dVar4 = *br;
  *cr = *ar * *br + -(*ai * *bi);
  *ci = dVar1 * dVar2 + dVar3 * dVar4;
  return 0;
}