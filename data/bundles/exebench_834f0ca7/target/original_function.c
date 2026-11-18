static void FindDivDiff5Coeff1 ( double a, double b, double c,
                                 double *dd )
{




  double ba, ca, cb;

  ba = (double)(1.0/(b-a)); ca = (double)(1.0/(c-a)); cb = (double)(1.0/(c-b));

  dd[1] = ba*ba*ca*ca;
  dd[0] = (double)(2.0*(ca+ba)*dd[1]);
  dd[3] = cb*cb*ba*ba;
  dd[2] = (double)(2.0*(cb-ba)*dd[3]);
  dd[5] = cb*cb*ca*ca;
  dd[4] = (double)(-2.0*(cb+ca)*dd[5]);
}