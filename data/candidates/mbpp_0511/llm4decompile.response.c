int func0(int num)
{
 int sum = 0;
 int i;

 for (i = 2; i * i <= num; i++) {
  while (num % i == 0) {
   sum += i;
   num /= i;
  }
 }

 return sum + num;
}