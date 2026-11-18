void __cdecl ltostr(unsigned int uiValue, char *pString)
{
  // Pre-emptively null-terminate the 8-character hex string
  pString[8] = '\0';

  // Process 4 bits (1 nibble) at a time, for 8 iterations (32 bits total)
  for (int i = 0; i < 8; ++i)
  {
    // Extract the least significant nibble
    unsigned int nibble = uiValue & 0xF;
    char c;

    // Map the nibble to its corresponding ASCII hex character
    if (nibble < 10)
    {
      c = nibble + '0';       // 0-9 -> '0'-'9' (48-57)
    }
    else
    {
      c = nibble + 'A' - 10;  // 10-15 -> 'A'-'F' (65-70)
    }

    // Place the character from right to left
    pString[7 - i] = c;

    // Shift to the next nibble
    uiValue >>= 4;
  }
}