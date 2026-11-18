int func0(int binary)
{
 int decimal = 0;
 int i = 0;
 int rem = 0;
 while(binary != 0)
 {
  rem = binary % 10;
  binary /= 10;
  decimal += rem * pow(2, i);
  ++i;
 }
 return decimal;
}