void atmcpy(double *in,double *out)

{
  double *out_local;
  double *in_local;
  
  *out = *in;
  out[1] = in[1];
  out[2] = in[2];
  return;
}