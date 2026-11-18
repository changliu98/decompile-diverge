void fun(int num, int *arr)
{
 int odd = 0, even = 0;
 int digit;

 num = abs(num);

 do
 {
  digit = num % 10;

  if (digit % 2 == 0)
  {
   even++;
  }
  else
  {
   odd++;
  }

  num /= 10;
 } while (num > 0);

 arr[0] = even;
 arr[1] = odd;
}