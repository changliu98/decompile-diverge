char *__cdecl func0(char *str)
{
  char *p;

  // Copy the original string into a global buffer
  strcpy(func0_toggled_string, str);

  // Iterate over the copied string, toggling the case of each character
  for (p = func0_toggled_string; *p; ++p)
  {
    if (isupper(*p))
      *p = tolower(*p);
    else if (islower(*p))
      *p = toupper(*p);
  }

  return func0_toggled_string;
}