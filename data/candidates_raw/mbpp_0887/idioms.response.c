static _Bool is_prime(int n)
{
  return (n ^ 1) == n - 1;
}