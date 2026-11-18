char *__cdecl func0(int N)
{
  char temp; // Temporary variable for swapping
  int i_0;   // Loop index for reversing the string
  int len;   // Length of the binary string
  char *bi;  // Binary string buffer
  int i;     // Loop index for iterating through digits
  int sum;   // Sum of the decimal digits
  char str[6]; // Buffer to hold the decimal string (max 5 digits + null)
  int Na;    // Unused copy of N

  Na = N;
  // Convert the number to a decimal string
  sprintf(str, "%d", (unsigned int)N);
  
  // Calculate the sum of the decimal digits
  sum = 0;
  for (i = 0; str[i]; ++i)
    sum += str[i] - '0';
    
  // Allocate a buffer for the binary string (32-bit integer max length is 32 chars)
  bi = (char *)malloc(0x21uLL); // 0x21 = 33 bytes
  len = 0;
  
  // Convert the sum to a binary string
  if (sum)
  {
    while (sum > 0)
    {
      bi[len++] = sum % 2 + '0';
      sum /= 2;
    }
  }
  else
  {
    len = 1;
    *bi = '0';
  }
  bi[len] = '\0';
  
  // Reverse the binary string to correct the order
  for (i_0 = 0; i_0 < len / 2; ++i_0)
  {
    temp = bi[i_0];
    bi[i_0] = bi[len - i_0 - 1];
    bi[len - i_0 - 1] = temp;
  }
  
  return bi;
}