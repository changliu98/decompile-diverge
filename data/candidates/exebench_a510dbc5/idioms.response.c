void chartobit(int val, char *str)
{
 int i = 8 - 1;
 while (i > 0)
 {
  str[i--] = (val % 2 == 1 ? '1' : '0');
  val /= 2;
 }
 str[0] = (val % 2 == 1 ? '1' : '0');
}