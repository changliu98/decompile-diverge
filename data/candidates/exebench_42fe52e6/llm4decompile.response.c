int itoa(char *a, int i)
{
 int len = 0, temp = 1, num = i;
 if (i == 0)
 {
  a[0] = '0';
  a[1] = '\0';
  return 2;
 }
 if (i < 0)
 {
  num = -i;
 }
 while (num % temp != num)
 {
  temp *= 10;
  len++;
 }
 if (i < 0)
 {
  len++;
 }
 temp = 1;
 while (--len >= 0)
 {
  a[len] = ((num - (num % temp)) / temp) % 10 + '0';
  temp *= 10;
 }
 if (i < 0)
 {
  a[0] = '-';
 }
 a[len] = '\0';
 return len;
}