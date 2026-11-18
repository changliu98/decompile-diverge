void MulDoubComp (double *aRe, double *aIm,
                  double bRe, double bIm,
                  double cRe, double cIm)
{
  *aRe = bRe*cRe + ((unsigned long long)(bIm*cIm) ^ (1ULL << 63));
  *aIm = bRe*cIm + bIm*cRe;
}