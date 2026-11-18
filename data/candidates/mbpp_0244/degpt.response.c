int func0(int inputValue)
{
  // Calculate the square root of N, cast to double for precision, then cast to int
  // Add 1 to the integer part of the square root
  // Square the result to get the smallest perfect square greater than N
  return ((int)sqrt((double)inputValue) + 1) * ((int)sqrt((double)inputValue) + 1);
}