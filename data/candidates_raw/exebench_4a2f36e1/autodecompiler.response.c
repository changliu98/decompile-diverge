static void rotate(double c, double s, double *x, double *y)
{
 double t;

 t = c * *x + s * *y;
 *y = s * *x - c * *y;
 *x = t;
}