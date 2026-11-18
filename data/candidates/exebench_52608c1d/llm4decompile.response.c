void MatrixM(int *a,int *b)
{
 int a0 = (a[0]*b[0] + a[1]*b[2])%100;
 int a1 = (a[0]*b[1] + a[1]*b[3])%100;
 int a2 = (a[2]*b[0] + a[3]*b[2])%100;
 int a3 = (a[2]*b[1] + a[3]*b[3])%100;
 a[0] = a0;
 a[1] = a1;
 a[2] = a2;
 a[3] = a3;
}