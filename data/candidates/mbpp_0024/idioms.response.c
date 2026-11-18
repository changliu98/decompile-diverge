int func0(int binary)
{
 int decimal = 0;
 int i = 0;
 while (binary != 0)
 {
  decimal += (int)pow(2, i) * (binary % 10);
  binary /= 10;
  i++;
 }
 return decimal;
}