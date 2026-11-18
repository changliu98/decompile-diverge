long jam_exponent(long number)




{
 long result = 1L;

 while (number > 0)
 {
  result *= 2;
  number = number >> 2;
 }

 return (result);
}