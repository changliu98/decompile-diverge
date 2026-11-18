int __cdecl func0(int base, int power)
{
  int digits[1000]; 
  int size = 1;
  digits[0] = 1;

  // Multiply the large number by 'base', 'power' times
  for (int p = 0; p < power; ++p)
  {
    int carry = 0;
    
    // Multiply each digit by 'base' and handle the carry
    for (int i = 0; i < size; ++i)
    {
      long temp = carry + (long)base * digits[i];
      digits[i] = temp % 10;
      carry = temp / 10;
    }
    
    // Handle remaining carry by expanding the number of digits
    while (carry > 0)
    {
      digits[size] = carry % 10;
      carry /= 10;
      ++size;
    }
  }

  // Sum all the digits of the final large number
  int sum = 0;
  for (int i = 0; i < size; ++i)
    sum += digits[i];

  return sum;
}