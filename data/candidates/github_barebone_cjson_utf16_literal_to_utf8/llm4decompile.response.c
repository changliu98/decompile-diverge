unsigned char utf16_literal_to_utf8(const unsigned char *input_pointer,
                                           const unsigned char *input_end,
                                           unsigned char **output_pointer) {
  unsigned char first_byte_mark = 0;
  unsigned char sequence_length = 6;
  unsigned char utf8_length = 0;
  unsigned char utf8_position = 0;
  unsigned long codepoint = 0;
  unsigned int first_code = 0;
  unsigned int second_code = 0;
  const unsigned char *first_sequence = input_pointer;
  const unsigned char *second_sequence = input_pointer;

  if (input_end - input_pointer < 6) {
    goto invalid_sequence;
  }

  first_code = parse_hex4(input_pointer + 2);
  if (first_code >= 0xD800 && first_code <= 0xDFFF) {
    goto invalid_sequence;
  }

  if (first_code >= 0xD800 && first_code <= 0xDBFF) {
    if (input_end - (input_pointer + 6) < 6) {
      goto invalid_sequence;
    }

    if (input_pointer[6] != '\\' || input_pointer[7] != 'u') {
      goto invalid_sequence;
    }

    second_sequence = input_pointer + 8;
    second_code = parse_hex4(second_sequence);
    if (second_code < 0xDC00 || second_code > 0xDFFF) {
      goto invalid_sequence;
    }

    codepoint = ((first_code & 0x3FF) << 10) | (second_code & 0x3FF);
    codepoint += 0x10000;
    sequence_length = 12;
  } else {
    codepoint = first_code;
  }

  if (codepoint < 0x80) {
    utf8_length = 1;
  } else if (codepoint < 0x800) {
    utf8_length = 2;
    first_byte_mark = 0xC0;
  } else if (codepoint < 0x10000) {
    utf8_length = 3;
    first_byte_mark = 0xE0;
  } else if (codepoint < 0x110000) {
    utf8_length = 4;
    first_byte_mark = 0xF0;
  } else {
    goto invalid_sequence;
  }

  utf8_position = utf8_length;
  while (utf8_position--) {
    (*output_pointer)[utf8_position] = (codepoint % 0x40) | 0x80;
    codepoint = codepoint >> 6;
  }

  if (utf8_length > 1) {
    (*output_pointer)[0] = first_byte_mark | codepoint;
  } else {
    (*output_pointer)[0] = codepoint;
  }

  *output_pointer += utf8_length;

  return sequence_length;

invalid_sequence:
  return 0;
}