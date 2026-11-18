void __cdecl convert2ASCII(char input, char *output)
{
  unsigned char high_nibble = (input >> 4) & 0xF;
  unsigned char low_nibble = input & 0xF;

  // Convert the high nibble
  if (high_nibble >= 10)
    output[0] = (high_nibble - 10) + 'a';
  else
    output[0] = high_nibble + '0';

  // Convert the low nibble
  if (low_nibble >= 10)
    output[1] = (low_nibble - 10) + 'a';
  else
    output[1] = low_nibble + '0';
}