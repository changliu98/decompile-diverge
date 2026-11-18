
static void FindDivDiff4Coeff ( double a, double b, double c, double d, double e,
                                double *dd )
{



  dd[0] = (double)(1.0/((a-b)*(a-c)*(a-d)*(a-e)));
  dd[1] = (double)(1.0/((b-a)*(b-c)*(b-d)*(b-e)));
  dd[2] = (double)(1.0/((c-a)*(c-b)*(c-d)*(c-e)));
  dd[3] = (double)(1.0/((d-a)*(d-b)*(d-c)*(d-e)));
  dd[4] = (double)(1.0/((e-a)*(e-b)*(e-c)*(e-d)));
}
