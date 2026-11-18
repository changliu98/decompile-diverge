char *str_tolower(char *text)
{
  int i = 0; int j = 0;
  while (text[i])
  {
    if (((*__ctype_b_loc ())[(int) ((text[i]))] & (unsigned short) _ISupper))
    {
      if (i && (((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (unsigned short) _ISlower) || ((*__ctype_b_loc ())[(int) ((text[i - 1]))] & (unsigned short) _ISdigit)))
      {
        str_tolower_buffer[j++] = '_';
      }
      str_tolower_buffer[j++] = tolower(text[i]);
    }
    else
    {
      str_tolower_buffer[j++] = text[i];
    }
    i++;
  }
  str_tolower_buffer[j] = '\0';
  return str_tolower_buffer;
}