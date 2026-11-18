int func0(int number)
{
  // Repeatedly divide n by 10 until n is less than or equal to 9
  for (; 9 < number; number = number / 10) {
  }
  // Return the last digit of the original number
  return number;
}