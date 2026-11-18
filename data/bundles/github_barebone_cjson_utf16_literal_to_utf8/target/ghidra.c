uchar utf16_literal_to_utf8(uchar *input_pointer,uchar *input_end,uchar **output_pointer)

{
  byte bVar1;
  uint uVar2;
  uint uVar3;
  uint second_code;
  uchar *second_sequence;
  uchar first_byte_mark;
  uchar sequence_length;
  uchar utf8_position;
  uchar utf8_length;
  uchar *first_sequence;
  uint first_code;
  unsigned_long codepoint;
  uchar **output_pointer_local;
  uchar *input_end_local;
  uchar *input_pointer_local;
  uchar local_9;
  
  first_byte_mark = '\0';
  if (((long)input_end - (long)input_pointer < 6) ||
     ((uVar2 = parse_hex4(input_pointer + 2), 0xdbff < uVar2 && (uVar2 < 0xe000)))) {
LAB_00105601:
    local_9 = '\0';
  }
  else {
    if ((uVar2 < 0xd800) || (0xdbff < uVar2)) {
      sequence_length = '\x06';
    }
    else {
      sequence_length = '\f';
      if (((((long)input_end - (long)(input_pointer + 6) < 6) || (input_pointer[6] != '\\')) ||
          (input_pointer[7] != 'u')) ||
         ((uVar3 = parse_hex4(input_pointer + 8), uVar3 < 0xdc00 || (0xdfff < uVar3))))
      goto LAB_00105601;
      uVar2 = ((uVar2 & 0x3ff) << 10 | uVar3 & 0x3ff) + 0x10000;
    }
    codepoint = (unsigned_long)uVar2;
    if (codepoint < 0x80) {
      utf8_length = '\x01';
      utf8_position = utf8_length;
    }
    else if (codepoint < 0x800) {
      utf8_length = '\x02';
      first_byte_mark = 0xc0;
      utf8_position = utf8_length;
    }
    else if (codepoint < 0x10000) {
      utf8_length = '\x03';
      first_byte_mark = 0xe0;
      utf8_position = utf8_length;
    }
    else {
      if (0x10ffff < codepoint) goto LAB_00105601;
      utf8_length = '\x04';
      first_byte_mark = 0xf0;
      utf8_position = utf8_length;
    }
    while( true ) {
      utf8_position = utf8_position + 0xff;
      bVar1 = (byte)codepoint;
      if (utf8_position == '\0') break;
      (*output_pointer)[utf8_position] = bVar1 & 0xbf | 0x80;
      codepoint = codepoint >> 6;
    }
    if (utf8_length < 2) {
      **output_pointer = bVar1 & 0x7f;
    }
    else {
      **output_pointer = bVar1 | first_byte_mark;
    }
    *output_pointer = *output_pointer + (int)(uint)utf8_length;
    local_9 = sequence_length;
  }
  return local_9;
}