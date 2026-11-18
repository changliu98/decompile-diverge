void complexMultiplication
               (double xReal,double xImag,double yReal,double yImag,double *zReal,double *zImag)

{
  double *zImag_local;
  double *zReal_local;
  double yImag_local;
  double yReal_local;
  double xImag_local;
  double xReal_local;
  
  *zReal = xReal * yReal + -(xImag * yImag);
  *zImag = xReal * yImag + xImag * yReal;
  return;
}