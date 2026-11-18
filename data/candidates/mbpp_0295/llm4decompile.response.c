int func0(int number)
{
 int i;
 int sum = 1;

 for (i = 2; i < number; i++)
  if (number % i == 0)
   sum += i;

 return sum;
}