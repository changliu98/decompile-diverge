double func0(int n, int r, double p)
{
 int i;
 double answer;

 if (r > n / 2)
  r = n - r;
 answer = 1.0;
 for (i = 1; i <= r; i++)
  answer = answer * (n - r + i) / i;

 return answer * pow(p, (double) r) * pow((1.0 - p), (double) (n - r));
}