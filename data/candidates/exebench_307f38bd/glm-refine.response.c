void __cdecl multiply(int factor1, int factor2, int *prod)
{
  // Calculate the true 64-bit product (using long long to prevent 32-bit overflow)
  long long true_product = (long long)factor1 * factor2;
  
  // Extract the lower 31 bits (equivalent to bitwise AND with 0x7FFFFFFF)
  int lower_31_bits = (int)(true_product & 0x7FFFFFFF);
  *prod = lower_31_bits;

  // Convert the true product to a double for floating-point scaling
  double d_product = (double)true_product;

  double scaled_result;
  // Check if the sign bit (bit 30) of the 31-bit truncated product is set
  if (lower_31_bits >= 0x40000000) 
  {
    // Bias by -2^29 and scale by 2^-31
    scaled_result = (d_product - 536870912.0) / 2147483648.0;
  }
  else
  {
    // Bias by +2^29 and scale by 2^-31
    scaled_result = (d_product + 536870912.0) / 2147483648.0;
  }
  
  // Store the integer-cast result into the second element of the output array
  prod[1] = (int)scaled_result;
}