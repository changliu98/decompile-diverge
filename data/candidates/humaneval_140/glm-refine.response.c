void __cdecl func0(const char *text, char *out)
{
  int space_len = 0;
  int j = 0;
  int text_len = strlen(text);

  for (int i = 0; i < text_len; ++i)
  {
    if (text[i] == ' ')
    {
      ++space_len;
    }
    else
    {
      // Replace accumulated spaces based on their count
      if (space_len == 1)
      {
        out[j++] = '_';
      }
      else if (space_len == 2)
      {
        out[j++] = '_';
        out[j++] = '_';
      }
      else if (space_len > 2)
      {
        out[j++] = '-';
      }
      
      space_len = 0;
      out[j++] = text[i];
    }
  }

  // Handle any trailing spaces at the end of the string
  if (space_len == 1)
  {
    out[j++] = '_';
  }
  else if (space_len == 2)
  {
    out[j++] = '_';
    out[j++] = '_';
  }
  else if (space_len > 2)
  {
    out[j++] = '-';
  }

  out[j] = '\0';
}