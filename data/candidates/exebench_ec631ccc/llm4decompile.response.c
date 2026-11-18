void lamda2x(double *lamda, double *x, double *h, double *boxlo)
{
    x[0] = boxlo[0] + lamda[0]*h[0] + lamda[1]*h[4] + lamda[2]*h[5];
    x[1] = boxlo[1] + lamda[1]*h[1] + lamda[2]*h[3];
    x[2] = boxlo[2] + lamda[2]*h[2];
}