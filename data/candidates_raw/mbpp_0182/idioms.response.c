void get_char_sets(char *string, char *uppercase_characters, char *lowercase_characters, char *numerical_characters, char *special_characters)
{
  int i; int len; int upper_idx = 0; int lower_idx = 0; int num_idx = 0; int special_idx = 0;
  len = strlen(string);
  for (i = 0; i < len; i++)
  {
    if (((*__ctype_b_loc ())[(int) ((string[i]))] & (unsigned short) _ISupper))
    {
      uppercase_characters[upper_idx++] = string[i];
    }
    else if (((*__ctype_b_loc ())[(int) ((string[i]))] & (unsigned short) _ISlower))
    {
      lowercase_characters[lower_idx++] = string[i];
    }
    else if (((*__ctype_b_loc ())[(int) ((string[i]))] & (unsigned short) _ISdigit))
    {
      numerical_characters[num_idx++] = string[i];
    }
    else if (string[i] == ',' || string[i] == '.' || string[i] == '!' || string[i] == '?')
    {
      special_characters[special_idx++] = string[i];
    }
  }
  uppercase_characters[upper_idx] = '\0';
  lowercase_characters[lower_idx] = '\0';
  numerical_characters[num_idx] = '\0';
  special_characters[special_idx] = '\0';
}