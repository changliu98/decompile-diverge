void right_shift_str(char *p, int n)
{
 int length_of_str = 0;
 char temp;
 char *q = p;

 while (*q++)
  length_of_str++;

 while (n--) {
  temp = *(p + length_of_str - 1);
  for (int i = length_of_str - 1; i > 0; i--)
   *(p + i) = *(p + i - 1);
  *p = temp;
 }
}