Represents the global variable func0_roman_num

char *__cdecl func0(int num)
{
  // The 13 standard symbols of Roman numerals, including subtractive combinations.
  // Initialized from the .rdata section (originally referenced via off_3D70).
  const char *symbols[13] = {
      "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"
  };
  
  // The corresponding integer values for each symbol.
  // Initialized from the .rdata section (originally referenced via unk_2010).
  const int values[13] = {
      1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1
  };

  int remaining = num;
  global_roman_num[0] = '\0'; // Reset the global string buffer (func0_roman_num = 0)
  
  for (int i = 0; remaining > 0; ++i)
  {
    while (remaining >= values[i])
    {
      strcat(global_roman_num, symbols[i]);
      remaining -= values[i];
    }
  }
  
  return global_roman_num;
}