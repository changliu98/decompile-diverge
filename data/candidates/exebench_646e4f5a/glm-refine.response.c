void __cdecl squeeze_alt(char *str1, char *str2)
{
  int j = 0;

  for (int i = 0; str1[i] != '\0'; ++i)
  {
    int found = 0;

    // Loop through str2 to check if str1[i] exists in it.
    // The loop breaks early if we reach the end of str2 or 
    // if a match has already been found.
    for (int k = 0; str2[k] != '\0' && found != 1; ++k)
    {
      if (str1[i] == str2[k])
        found = 1;
    }

    // If the character was not found in str2, keep it in str1
    if (!found)
    {
      str1[j] = str1[i];
      ++j;
    }
  }
  
  // Null-terminate the squeezed string
  str1[j] = '\0';
}