void ZVdotC21(int n, double *rA, double *iA, double *rX, double *rY)
{
  double rAr, iAr, rAi, iAi, rXr, iXi, rYr, iYi;
  double rZr = 0.0, rZi = 0.0, iZr = 0.0, iZi = 0.0;
  int i, j;

  i = 0;
  j = 0;
  while (1) {
    if (j >= n) break;
    rAr = rA[i]; iAr = rA[i+1];
    rAi = iA[i]; iAi = iA[i+1];
    rXr = rX[i]; iXi = rX[i+1];

    rZr += rAr*rXr + iAr*iXi;
    rZi += rAr*iXi + iAr*rXr;
    iZr += rAi*rXr + iAi*iXi;
    iZi += rAi*iXi + iAi*rXr;

    j++;
    i += 2;
  }
  rY[0] = rZr; rY[1] = rZi;
  rY[2] = iZr; rY[3] = iZi;
}