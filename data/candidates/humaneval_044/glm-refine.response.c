void __cdecl func0(int x, int base, char *out)
{
  char temp[33];
  int length = 0;

  // Convert the number to the given base (digits are stored in reverse order)
  while (x > 0)
  {
    // x % base gets the digit, + 48 converts it to an ASCII character ('0' is 48)
    temp[length++] = (x % base) + 48;
    x /= base;
  }

  // Reverse the digits and write them to the output buffer
  for (int i = 0; i < length; ++i)
  {
    out[i] = temp[length - 1 - i];
  }

  // Null-terminate the string
  out[length] = '\0';
}