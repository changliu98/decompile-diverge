int __cdecl func0(const char *s)
{
  int int_val = 0;
  int len = strlen(s);
  
  // Lookup table mapping Roman numeral characters to their integer values.
  // Indices correspond to ASCII values: 'C'=67, 'D'=68, 'I'=73, 'L'=76, 'M'=77, 'V'=86, 'X'=88.
  int rom_val[256] = {0};
  rom_val['I'] = 1;
  rom_val['V'] = 5;
  rom_val['X'] = 10;
  rom_val['L'] = 50;
  rom_val['C'] = 100;
  rom_val['D'] = 500;
  rom_val['M'] = 1000;

  for (int i = 0; i < len; ++i)
  {
    // If the current character's value is greater than the previous one, 
    // it means we encountered a subtractive combination (e.g., IV, IX, XL).
    // We subtract twice the previous value because it was erroneously added 
    // in the previous iteration, and we need to subtract it once more to 
    // account for the actual subtractive notation.
    if (i > 0 && rom_val[s[i]] > rom_val[s[i - 1]])
    {
      int_val += rom_val[s[i]] - 2 * rom_val[s[i - 1]];
    }
    else
    {
      // Otherwise, simply add the current character's value.
      int_val += rom_val[s[i]];
    }
  }
  
  return int_val;
}