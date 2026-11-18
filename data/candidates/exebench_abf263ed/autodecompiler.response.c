void ZVdotU22(int n, double *A, double *B, double *C, double *D, double *m)
{
 int i, j;
 double a, b, c, d, e, f, g, h, k, l, o, p, q, r, s, t;
 double m00, m01, m10, m11, m20, m21, m30, m31;

 m00 = 0; m01 = 0; m10 = 0; m11 = 0; m20 = 0; m21 = 0; m30 = 0; m31 = 0;
 i = 0;
 j = 0;
 k = 1;
 while (1) {
  if (i < n) {
   a = A[j]; b = A[k];
   c = B[j]; d = B[k];
   e = C[j]; f = C[k];
   g = D[j]; h = D[k];

   m00 += a*e + b*f;
   m01 += a*f + b*e;
   m10 += a*g + b*h;
   m11 += a*h + b*g;
   m20 += c*e + d*f;
   m21 += c*f + d*e;
   m30 += c*g + d*h;
   m31 += c*h + d*g;
   i++;
   j += 2;
   k += 2;
  } else {
   break;
  }
 }

 m[0] = m00; m[1] = m01; m[2] = m10; m[3] = m11;
 m[4] = m20; m[5] = m21; m[6] = m30; m[7] = m31;
}