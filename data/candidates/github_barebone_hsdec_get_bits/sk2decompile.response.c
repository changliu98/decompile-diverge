static unsigned short get_bits(LHADecodeStatus *status, unsigned char n) {
  unsigned short bits = 0;
  int i;
  if (n > 15) {
    return 0xffff;
  }
  if (status->input_size == 0 && status->mask < (1 << (n - 1))) {
    return 0xffff;
  }
  for (i = 0; i < n; i++) {
    if (status->mask == 0) {
      if (status->input_size == 0) {
        return 0xffff;
      }
      status->input_byte = status->input_buffer[status->input_index++];
      if (status->input_index == status->input_size) {
        status->input_index = 0;
        status->input_size = 0;
      }
      status->mask = 0x80;
    }
    bits <<= 1;
    if (status->input_byte & status->mask) {
      bits |= 1;
    }
    status->mask >>= 1;
  }
  return bits;
}