void complexMultiplication( double xRe, double xIm, double yRe, double yIm,
                  double *zRe, double *zIm )
{
   *zRe = xRe * yRe + ((double) -1.0) * xIm * yIm;
   *zIm = xRe * yIm + xIm * yRe;
}