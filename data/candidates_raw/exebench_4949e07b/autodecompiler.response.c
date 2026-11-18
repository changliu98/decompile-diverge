static void add2(double *z)
{
 double t;

 t = z[0] - z[2];
 z[0] += z[1];
 z[1] += z[3];
 z[2] = t;
 z[3] = z[1] - z[3];
}