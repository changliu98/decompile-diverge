int maxdig(int *num, int *max)
{
 int temp;
 if(*num == 0)
 {
  temp = *max;
  return temp;
 }
 dig = *num % 10;
 if(dig >= *max)
 {
  *max = dig;
 }
 *num = *num / 10;
 maxdig(num, max);
}