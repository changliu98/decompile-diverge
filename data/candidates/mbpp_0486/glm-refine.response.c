probability of success on a single trial
double __cdecl func0(int n, int r, double p)
{
  double binomial_coeff; // [rsp+10h] [rbp-30h]
  int i;                 // [rsp+1Ch] [rbp-24h]
  double answer;         // [rsp+20h] [rbp-20h]
  int k;                 // [rsp+38h] [rbp-8h]

  // Optimize the combination calculation C(n, r) by using the smaller of r or n - r
  // This avoids unnecessary loop iterations and reduces the risk of overflow.
  k = r;
  if (r > n / 2)
    k = n - r;

  answer = 1.0;
  
  // Compute the binomial coefficient: C(n, k) = n! / (k! * (n - k)!)
  // The loop evaluates: Product for i=1 to k of [(n - k + i) / i]
  for (i = 1; i <= k; ++i)
    answer = (double)(n - k + i) * answer / (double)i;

  binomial_coeff = answer;

  // Binomial distribution formula: P(X = r) = C(n, r) * p^r * (1 - p)^(n - r)
  return binomial_coeff * pow(p, (double)r) * pow(1.0 - p, (double)(n - r));
}