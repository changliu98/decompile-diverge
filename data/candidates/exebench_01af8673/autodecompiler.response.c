static void ecRotate(double *a, double b, double c)
{
 double t = a[2] * b + a[1] * c;
 a[2] = a[2] * c + (a[1] * b ^ ((unsigned long long)(1) << 63));
 a[1] = t;
}