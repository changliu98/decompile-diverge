int convert_dec_to_octal(int decimal)
{
 int octal = 0, i = 1, remainder;

 while (decimal != 0) {
  remainder = decimal % 8;
  octal += (remainder * i);
  i *= 10;
  decimal /= 8;
 }

 return octal;
}