int func0(int n)
{
 int count = 0;
 int i;
 int total;
 int j;
 int temp;

 for (i = 2; i * i <= n; i++) {
  total = 0;
  while (n % i == 0) {
   total++;
   n /= i;
  }
  j = 1;
  temp = 0;
  while (temp + j <= total) {
   count++;
   temp += j;
   j++;
  }
 }
 if (n != 1)
  count++;
 return count;
}