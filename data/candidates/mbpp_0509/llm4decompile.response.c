int func0(int n)
{
 int sum, count, avg;

 if(n%2 == 0)
 {
  printf("Invalid Input\n");
  return -1;
 }

 sum = 0;
 count = 0;
 while(n > 0)
 {
  sum = sum + n;
  n = n - 2;
  count++;
 }
 avg = sum / count;
 return avg;
}