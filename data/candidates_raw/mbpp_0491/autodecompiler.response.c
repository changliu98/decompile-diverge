double LpCurveDnRs (double maxLpDnRs, int lpInd, double lpRs)
{
 double curveDnRs;

 curveDnRs = maxLpDnRs * (1.0 - pow (lpRs, (double) lpInd)) / (1.0 - lpRs);

 return curveDnRs;
}