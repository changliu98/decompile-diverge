void __cdecl cenitPolarCrypt(char *str)
{
  const char *cenit = "cenitcenitpolar"; // Source alphabet
  const char *polar = "polarpolarceni";  // Target alphabet

  // Iterate through each character of the input string
  for (char *current_char = str; *current_char; ++current_char)
  {
    // Check if the character exists in our cipher alphabet
    for (int i = 0; cenit[i]; ++i)
    {
      if (*current_char == cenit[i])
      {
        // If it matches, swap it with the corresponding character
        *current_char = polar[i];
        break;
      }
    }
  }
}