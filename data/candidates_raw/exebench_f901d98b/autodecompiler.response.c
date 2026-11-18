void Compute_Moments(double *series, int n, double *moments,
       double A, double B, int Beta) {

 int i;
 double M1=0, M2=0, M3=0, p;

 if ((A==0) && (B==0))
  for(i=1; i<=n; i++) {
   M1 += series[i-1];
   if (Beta==0) {
    M2 += series[i-1]*(n-i);
    M3 += series[i-1]*(n-i)*(n-i-1);
   }
   if (Beta==1) {
    M2 += series[i-1]*(i-1);
    M3 += series[i-1]*(i-1)*(i-2);
   }
  }

 else
  for(i=1; i<=n; i++) {
   M1 += series[i-1];
   p = (i+A)/(n+B);
   if (Beta==0) {
    M2 += series[i-1]*(1-p);
    M3 += series[i-1]*(1-p)*(1-p);
   }
   if (Beta==1) {
    M2 += series[i-1]*p;
    M3 += series[i-1]*p*p;
   }
  }

 moments[0] = M1/n;
 moments[1] = M2/n/(n-1);
 moments[2] = M3/n/(n-1)/(n-2);

}