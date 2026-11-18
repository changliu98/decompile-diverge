/*
 * sgml__utf8_get_char - Decode the next UTF-8 character from the input string.
 *
 * @in: Pointer to the current position in the UTF-8 encoded string.
 * @chr: Pointer to an integer where the decoded Unicode code point will be stored.
 *
 * Returns: Pointer to the byte immediately following the decoded character.
 *
 * This function handles UTF-8 sequences of 1 to 6 bytes. It validates the
 * continuation bytes (must have the form 10xxxxxx) and extracts the code point.
 * Note: The 5-byte and 6-byte UTF-8 sequences are non-standard and typically
 * not used in valid UTF-8, but are included here for completeness or legacy
 * reasons.
 */
char * sgml__utf8_get_char(char *input_ptr, int *code_point_ptr)
{
  /* Handle 2-byte UTF-8 sequence: 110xxxxx 10xxxxxx */
  if ((((int)*input_ptr & 0xe0U) == 0xc0) && (((int)input_ptr[1] & 0xc0U) == 0x80)) {
    /* Extract 5 bits from first byte and 6 bits from second byte */
    *code_point_ptr = ((int)*input_ptr & 0x1fU) << 6 | (int)input_ptr[1] & 0x3fU;
    return input_ptr + 2;
  }
  /* Handle 3-byte UTF-8 sequence: 1110xxxx 10xxxxxx 10xxxxxx */
  else if ((((int)*input_ptr & 0xf0U) == 0xe0) &&
          ((((int)input_ptr[1] & 0xc0U) == 0x80 && (((int)input_ptr[2] & 0xc0U) == 0x80)))) {
    /* Extract 4 bits from first byte, 6 from second, 6 from third */
    *code_point_ptr = ((int)*input_ptr & 0xfU) << 0xc | ((int)input_ptr[1] & 0x3fU) << 6 | (int)input_ptr[2] & 0x3fU;
    return input_ptr + 3;
  }
  /* Handle 4-byte UTF-8 sequence: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
  else if ((((int)*input_ptr & 0xf8U) == 0xf0) &&
          (((((int)input_ptr[1] & 0xc0U) == 0x80 && (((int)input_ptr[2] & 0xc0U) == 0x80)) &&
           (((int)input_ptr[3] & 0xc0U) == 0x80)))) {
    /* Extract 3 bits from first byte, 6 from each of the next three */
    *code_point_ptr = ((int)*input_ptr & 7U) << 0x12 | ((int)input_ptr[1] & 0x3fU) << 0xc | ((int)input_ptr[2] & 0x3fU) << 6 |
           (int)input_ptr[3] & 0x3fU;
    return input_ptr + 4;
  }
  /* Handle 5-byte UTF-8 sequence (non-standard): 111110xx 10xxxxxx ... */
  else if (((((int)*input_ptr & 0xfcU) == 0xf8) && (((int)input_ptr[1] & 0xc0U) == 0x80)) &&
          ((((int)input_ptr[2] & 0xc0U) == 0x80 &&
           ((((int)input_ptr[3] & 0xc0U) == 0x80 && (((int)input_ptr[4] & 0xc0U) == 0x80)))))) {
    /* Extract 2 bits from first byte, 6 from each of the next four */
    *code_point_ptr = ((int)*input_ptr & 3U) << 0x18 | ((int)input_ptr[1] & 0x3fU) << 0x12 | ((int)input_ptr[2] & 0x3fU) << 0xc |
           ((int)input_ptr[3] & 0x3fU) << 6 | (int)input_ptr[4] & 0x3fU;
    return input_ptr + 5;
  }
  /* Handle 6-byte UTF-8 sequence (non-standard): 1111110x 10xxxxxx ... */
  else if ((((int)*input_ptr & 0xfeU) == 0xfc) &&
          ((((((int)input_ptr[1] & 0xc0U) == 0x80 && (((int)input_ptr[2] & 0xc0U) == 0x80)) &&
            (((int)input_ptr[3] & 0xc0U) == 0x80)) &&
           ((((int)input_ptr[4] & 0xc0U) == 0x80 && (((int)input_ptr[5] & 0xc0U) == 0x80)))))) {
    /* Extract 1 bit from first byte, 6 from each of the next five */
    *code_point_ptr = ((int)*input_ptr & 1U) << 0x1e | ((int)input_ptr[1] & 0x3fU) << 0x18 | ((int)input_ptr[2] & 0x3fU) << 0x12 |
           ((int)input_ptr[3] & 0x3fU) << 0xc | ((int)input_ptr[4] & 0x3fU) << 6 | (int)input_ptr[5] & 0x3fU;
    return input_ptr + 4;
  }
  /* Handle single-byte ASCII character: 0xxxxxxx */
  else {
    *code_point_ptr = (int)*input_ptr;
    return input_ptr + 1;
  }
}