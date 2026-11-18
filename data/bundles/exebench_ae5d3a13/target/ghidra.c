void sum(double *a,int len,double *retVal)

{
  int i;
  double acc;
  double *retVal_local;
  int len_local;
  double *a_local;
  
  acc = 0.0;
  for (i = 0; i < len; i = i + 1) {
    acc = a[i] + acc;
  }
  *retVal = acc;
  return;
}