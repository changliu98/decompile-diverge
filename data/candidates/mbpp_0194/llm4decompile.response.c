int func0(int n)
{
 int dec_value = 0;
 int base = 1;
 int temp = n;
 while (temp) {
  dec_value = (temp % 10) * base + dec_value;
  temp = temp / 10;
  base *= 8;
 }
 return dec_value;
}