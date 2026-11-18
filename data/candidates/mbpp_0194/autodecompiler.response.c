int func0(int oct)
{
 int last_digit, num, base, dec;
 num = oct;
 dec = 0;
 base = 1;

 while(num)
 {
  last_digit = num % 10;
  num = num / 10;
  dec += last_digit * base;
  base *= 8;
 }

 return dec;
}