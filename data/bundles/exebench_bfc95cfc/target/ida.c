void __cdecl oct_to_word(char *three_chars, char oct)
{
  char octa; // [rsp+1h] [rbp-9h]

  if ( three_chars )
  {
    *three_chars = (oct & 0xC0) >> 6;
    three_chars[1] = (oct & 0x38) >> 3;
    three_chars[2] = oct & 7;
    for ( octa = 0; octa < 3; ++octa )
      three_chars[octa] += 48;
  }
}