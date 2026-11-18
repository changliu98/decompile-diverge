// Function to calculate the product of the last digits of the absolute values of two integers
int func0(int num1, int num2)
{
  // Compute the absolute value of 'a', take modulo 10 to get its last digit,
  // compute the absolute value of 'b', take modulo 10 to get its last digit,
  // and return the product of these two last digits
  return (abs(num1) % 10) * (abs(num2) % 10);
}