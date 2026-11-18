int intwt(double N, double *W)
{
 int iN;
 if (N < 1.0) {
  iN = 1;
  *W = N;
 } else {
  iN = (int) N;
  *W = 1.0;
 }
 return iN;
}