unsigned __int8 __cdecl utf16_literal_to_utf8(
        const unsigned __int8 *const input_pointer,
        const unsigned __int8 *const input_end,
        unsigned __int8 **output_pointer)
{
  unsigned int second_code; // [rsp+4h] [rbp-4Ch]
  unsigned __int8 first_byte_mark; // [rsp+14h] [rbp-3Ch]
  char sequence_length; // [rsp+15h] [rbp-3Bh]
  unsigned __int8 utf8_position; // [rsp+16h] [rbp-3Ah]
  unsigned __int8 utf8_length; // [rsp+17h] [rbp-39h]
  unsigned int first_code; // [rsp+24h] [rbp-2Ch]
  unsigned __int64 codepoint; // [rsp+28h] [rbp-28h]

  first_byte_mark = 0;
  if ( input_end - input_pointer < 6 )
    return 0;
  first_code = parse_hex4(input_pointer + 2);
  if ( first_code >= 0xDC00 && first_code <= 0xDFFF )
    return 0;
  if ( first_code < 0xD800 || first_code > 0xDBFF )
  {
    sequence_length = 6;
    codepoint = first_code;
  }
  else
  {
    sequence_length = 12;
    if ( input_end - (input_pointer + 6) < 6 )
      return 0;
    if ( input_pointer[6] != 92 )
      return 0;
    if ( input_pointer[7] != 117 )
      return 0;
    second_code = parse_hex4(input_pointer + 8);
    if ( second_code < 0xDC00 || second_code > 0xDFFF )
      return 0;
    codepoint = (second_code & 0x3FF | ((first_code & 0x3FF) << 10)) + 0x10000;
  }
  if ( codepoint >= 0x80 )
  {
    if ( codepoint >= 0x800 )
    {
      if ( codepoint >= 0x10000 )
      {
        if ( codepoint > 0x10FFFF )
          return 0;
        utf8_length = 4;
        first_byte_mark = -16;
      }
      else
      {
        utf8_length = 3;
        first_byte_mark = -32;
      }
    }
    else
    {
      utf8_length = 2;
      first_byte_mark = -64;
    }
  }
  else
  {
    utf8_length = 1;
  }
  for ( utf8_position = utf8_length - 1; utf8_position; --utf8_position )
  {
    (*output_pointer)[utf8_position] = codepoint & 0x3F | 0x80;
    codepoint >>= 6;
  }
  if ( utf8_length <= 1u )
    **output_pointer = codepoint & 0x7F;
  else
    **output_pointer = first_byte_mark | codepoint;
  *output_pointer += utf8_length;
  return sequence_length;
}