void dual_mul(double ar,double ad,double br,double bd,double *cr,double *cd)

{
  double *cd_local;
  double *cr_local;
  double bd_local;
  double br_local;
  double ad_local;
  double ar_local;
  
  *cr = ar * br;
  *cd = ar * bd + ad * br;
  return;
}