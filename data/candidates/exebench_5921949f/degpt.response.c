void factorial(double *factorial_array)
{
  // Initialize the first element of the factorial array with a predefined constant value
  *factorial_array = DAT_00102008;
  
  // Iterate 20 times (0x14 in hexadecimal) to compute factorials
  for (int count = 0; count < 0x14; count++) {
    // Calculate the factorial of (count + 1) by multiplying (count + 1) with the previous factorial value
    factorial_array[count + 1] = (double)(count + 1) * factorial_array[count];
  }
}