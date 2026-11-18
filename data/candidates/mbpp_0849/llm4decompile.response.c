int func0(int N)
{
 int SumOfPrimeDivisors[N+1];
 int i, j;

 for (i = 0; i <= N; i++)
  SumOfPrimeDivisors[i] = 0;

 for (i = 2; i <= N; i++)
  if (SumOfPrimeDivisors[i] == 0)
   for (j = i; j <= N; j += i)
    SumOfPrimeDivisors[j] += i;

 return SumOfPrimeDivisors[N];
}