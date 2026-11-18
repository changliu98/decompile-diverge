float dotprod(float *v, float *u, int n)
{
    int i;
    float sum = 0.0;

    for (i = 0; ; i++) {
 if (i < n) {
     sum += v[i] * u[i];
 } else {
     return sum;
 }
    }
}