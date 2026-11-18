int clk_div_even_up(int number)
{
 int result;

 if(number == 1)
  result = 1;
 else
  result = (number + 1) & ~1;

 return result;
}