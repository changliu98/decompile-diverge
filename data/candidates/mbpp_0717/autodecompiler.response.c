double func0(double *x, int n)
{
 double avg, sum;
 int i;

 if(n < 2)
 {
  return 0.0;
 }

 avg = avg_calc(x, n);
 sum = 0.0;
 for(i = 0; ; i++)
 {
  if(i >= n) break;
  sum += (x[i] - avg) * (x[i] - avg);
 }
 sum = sqrt(sum / (double)(n - 1));
 return sum;
}