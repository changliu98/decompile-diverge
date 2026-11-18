void mysign(double *in,double *out,int n)
{
  int i,n1;
  double t;

  *out=1.0;
  n1=(double *)out-(double *)in+1;
  for(i=0;i<n1;i++)
    {
      *out=((*out) && ((in[i]>=0)?1:0))?1:0;
    }
}