int func0(int n)
{
 int result = 1;


 while (n % 2 == 0)
 {
  n /= 2;
 }

 int factor = 3;
 int max_factor = (int)sqrt((double)n) + 1;

 while (factor < max_factor)
 {
  int sum = 1;
  int term = 1;

  while (n % factor == 0)
  {
   term *= factor;
   sum += term;
   n /= factor;
  }

  result *= sum;
  factor += 2;
 }

 if (n > 1)
 {
  result *= (n + 1);
 }

 return result;
}