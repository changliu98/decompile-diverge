int func0(char *str)
{
  int flag_l = 0;
  int flag_n = 0;
  for ( ; *str != '\0'; str++ )
  {
    if ( ((*__ctype_b_loc ())[(int) (((unsigned char)*str))] & (unsigned short) _ISalpha) )
      flag_l = 1;
    if ( ((*__ctype_b_loc ())[(int) (((unsigned char)*str))] & (unsigned short) _ISdigit) )
      flag_n = 1;
  }
  return (flag_l && flag_n);
}