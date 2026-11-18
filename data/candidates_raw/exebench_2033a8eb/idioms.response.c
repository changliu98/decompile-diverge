void complex_mul(double *zReal, double *zImag, double xReal, double xImag, double yReal, double yImag)
{
  *zReal = xReal * yReal - xImag * yImag;
  *zImag = xReal * yImag + xImag * yReal;
}