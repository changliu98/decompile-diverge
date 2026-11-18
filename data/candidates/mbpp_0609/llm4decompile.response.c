int func0(int A, int B, int N)
{
 int tmp = B - 1;
 if (tmp > N)
  tmp = N;
 return (tmp * A) / B;
}