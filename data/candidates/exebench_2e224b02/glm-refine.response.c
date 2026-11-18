void __cdecl prtl16(long num, char *str)
{
  char temp[9];
  int i;
  long numa = num;
  char *stra = str;

  temp[0] = 0;
  
  // Convert the number to hex characters in reverse order
  for (i = 1; i <= 8; ++i)
  {
    temp[i] = "0123456789abcdef"[numa & 0xF];
    numa >>= 4;
  }
  
  // Skip leading zeros
  for (i = 8; temp[i] == '0'; --i)
    ;
  
  // If the number was 0, keep one '0' character
  if (!i)
    i = 1;
  
  // Copy the characters to the output string
  while (i >= 0)
  {
    *stra++ = temp[i--];
  }
}