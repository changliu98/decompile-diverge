static void FindDivDiff5Coeff2 ( double a, double b, double c, double d,
                                 double *dd )
{




  double ba, ca, cb, da, db, dc;

  ba = (double)(1.0/(b-a)); ca = (double)(1.0/(c-a)); cb = (double)(1.0/(c-b));
  da = (double)(1.0/(d-a)); db = (double)(1.0/(d-b)); dc = (double)(1.0/(d-c));

  dd[0] = -ba*ba*ca*ca*da;
  dd[1] = (double)(-(db+2.0*cb-ba)*ba*db*cb*cb);
  dd[2] = -ba*db*cb*cb;
  dd[3] = (double)(-(dc-2.0*cb-ca)*dc*ca*cb*cb);
  dd[4] = -dc*ca*cb*cb;
  dd[5] = da*db*db*dc*dc;
}