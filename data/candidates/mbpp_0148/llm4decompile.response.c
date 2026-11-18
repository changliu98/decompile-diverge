int func0(int N)
{
 int M = closest(N);
 return sum_digits_single(M) + sum_digits_single(N-M);
}