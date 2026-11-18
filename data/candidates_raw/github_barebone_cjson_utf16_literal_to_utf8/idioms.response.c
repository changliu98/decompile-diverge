static unsigned char parse_utf8(unsigned char *input, unsigned char *input_end, unsigned char **output)
{
  unsigned int first_code;
  unsigned int second_code;
  unsigned long codepoint;
  unsigned char sequence_length;
  unsigned char utf8_length;
  unsigned char utf8_position;
  unsigned char first_byte_mark = 0;
  if (input_end - input < 6)
    return 0;
  first_code = parse_hex4(input + 2);
  if (first_code >= 0xd800 && first_code <= 0xdfff)
    return 0;
  if (first_code >= 0xd800 && first_code <= 0xdbff)
  {
    sequence_length = 12;
    if (input_end - (input + sequence_length) < 6)
      return 0;
    if (input[6] != '\\')
      return 0;
    if (input[7] != 'u')
      return 0;
    second_code = parse_hex4(input + 8);
    if (second_code < 0xd800 || second_code > 0xdfff)
      return 0;
    codepoint = ((first_code & 0x3ff) << 10) | (second_code & 0x3ff) + 0x10000;
  }
  else
  {
    sequence_length = 6;
    codepoint = first_code;
  }
  if (codepoint < 0x80)
    utf8_length = 1;
  else if (codepoint < 0x800)
    utf8_length = 2;
  else if (codepoint < 0x10000)
    utf8_length = 3;
  else if (codepoint <= 0x10ffff)
    utf8_length = 4;
  else
    return 0;
  if (utf8_length > 1)
    first_byte_mark = -utf8_length << 3;
  for (utf8_position = utf8_length - 1; utf8_position > 0; utf8_position--)
  {
    (*output)[utf8_position] = (codepoint & 0x3f) | 0x80;
    codepoint >>= 6;
  }
  if (utf8_length > 1)
    (*output)[0] = (codepoint & 0x1f) | first_byte_mark;
  else
    (*output)[0] = (codepoint & 0x7f);
  *output += utf8_length;
  return sequence_length;
}