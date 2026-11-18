void __cdecl hex_to_word(char *two_chars, char hex)
{
  char v2; // dl
  char hexa; // [rsp+1h] [rbp-9h]

  if ( two_chars )
  {
    *two_chars = (hex & 0xF0) >> 4;
    two_chars[1] = hex & 0xF;
    for ( hexa = 0; hexa < 2; ++hexa )
    {
      if ( two_chars[hexa] <= 9 )
        v2 = two_chars[hexa] + 48;
      else
        v2 = two_chars[hexa] + 55;
      two_chars[hexa] = v2;
    }
  }
}