void __cdecl oct_to_word(char *three_chars, char oct)
{
  if ( three_chars )
  {
    // Extract the three 3-bit segments from the octet and map them to ASCII '0'-'7'
    three_chars[0] = ((oct >> 6) & 3) + '0';
    three_chars[1] = ((oct >> 3) & 7) + '0';
    three_chars[2] = (oct & 7) + '0';
  }
}