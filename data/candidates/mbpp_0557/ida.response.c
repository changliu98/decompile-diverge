char *__cdecl func0(char *string)
{
  int i; // [rsp+4h] [rbp-Ch]

  strcpy(func0_toggled_string, string);
  for ( i = 0; func0_toggled_string[i]; ++i )
  {
    if ( ((*__ctype_b_loc())[func0_toggled_string[i]] & 0x100) != 0 )
    {
      func0_toggled_string[i] = tolower(func0_toggled_string[i]);
    }
    else if ( ((*__ctype_b_loc())[func0_toggled_string[i]] & 0x200) != 0 )
    {
      func0_toggled_string[i] = toupper(func0_toggled_string[i]);
    }
  }
  return func0_toggled_string;
}