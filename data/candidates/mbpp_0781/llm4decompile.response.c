char* func0(int n)
{
 int i, count = 0;
 for (i = 1; i < sqrt(n) + 2; i++)
 {
  if (n % i == 0)
  {
   if (n / i == i)
    count++;
   else
    count += 2;
  }
 }
 return (count % 2) ? "Odd" : "Even";
}