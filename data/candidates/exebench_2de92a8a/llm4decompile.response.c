int sprint_int_number_nonlocalized(char *string, int number, int minimum, int sign)
{
 int base = 1000000000;
 int i, j, k;
 int flag = 0;

 if (minimum < 0)
  minimum = 0;

 if (minimum > 9)
  flag = 1;

 if (number < 0)
 {
  string[0] = '-';
  j = 1;
  number = number * -1;
 }
 else
 {
  if (sign)
  {
   string[0] = '+';
   j = 1;
  }
  else
   j = 0;
 }

 for (i = 10; i; i--)
 {
  if (minimum == i)
   flag = 1;

  k = number / base;
  number = number % base;

  if (k || flag)
  {
   string[j] = k + '0';
   j++;
   flag = 1;
  }

  base = base / 10;
 }

 if (!flag)
 {
  string[j] = '0';
  j++;
 }

 string[j] = '\0';

 return(j);
}