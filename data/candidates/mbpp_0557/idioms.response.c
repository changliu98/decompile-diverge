char *func0(char *string)
{
  int i;
  strcpy(func0_toggled_string, string);
  for (i = 0; func0_toggled_string[i]; i++)
  {
    if (((*__ctype_b_loc ())[(int) ((func0_toggled_string[i]))] & (unsigned short) _ISupper))
    {
      func0_toggled_string[i] = tolower(func0_toggled_string[i]);
    }
    else if (((*__ctype_b_loc ())[(int) ((func0_toggled_string[i]))] & (unsigned short) _ISlower))
    {
      func0_toggled_string[i] = toupper(func0_toggled_string[i]);
    }
  }
  return (func0_toggled_string);
}