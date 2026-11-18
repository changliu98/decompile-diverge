int __cdecl parse_uuid(char *str, int *uuid)
{
  char c;
  int hex_val;
  int hex_count = 0;
  int i;

  // Initialize the 128-bit UUID (4 x 32-bit integers) to 0
  for (i = 0; i < 4; ++i)
    uuid[i] = 0;

  // Iterate through each character in the string
  while ((c = *str++) != '\0')
  {
    // Parse hexadecimal digit value
    if (c >= '0' && c <= '9')
    {
      hex_val = c - '0';
    }
    else if (c >= 'a' && c <= 'f')
    {
      hex_val = c - 'a' + 10;
    }
    else if (c >= 'A' && c <= 'F')
    {
      hex_val = c - 'A' + 10;
    }
    else
    {
      // Ignore valid UUID separators. If it's an invalid char, fail.
      if (!strchr(":. -", c))
        return 0;
      continue;
    }

    // Only pack the first 32 valid hex characters into the UUID array
    if (hex_count < 32)
    {
      // Shift the current 32-bit block left by 4 bits and add the new nibble
      uuid[hex_count / 8] = (uuid[hex_count / 8] * 16) + hex_val;
    }
    
    // Keep track of all valid hex characters encountered (even beyond 32)
    hex_count++;
  }

  // Success only if exactly 32 hex characters were found
  return hex_count == 32;
}