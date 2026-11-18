int read_int_delta(uint8_t *in,uint32_t *out,uint32_t *prev)

{
  uint32_t *prev_local;
  uint32_t *out_local;
  uint8_t *in_local;
  int local_c;
  
  *out = *in & 0x7f;
  if (*in < 0x80) {
    *prev = *out + *prev;
    *out = *prev;
    local_c = 1;
  }
  else {
    *out = (in[1] & 0x7f) << 7 | *out;
    if (in[1] < 0x80) {
      *prev = *out + *prev;
      *out = *prev;
      local_c = 2;
    }
    else {
      *out = (in[2] & 0x7f) << 0xe | *out;
      if (in[2] < 0x80) {
        *prev = *out + *prev;
        *out = *prev;
        local_c = 3;
      }
      else {
        *out = (in[3] & 0x7f) << 0x15 | *out;
        if (in[3] < 0x80) {
          *prev = *out + *prev;
          *out = *prev;
          local_c = 4;
        }
        else {
          *out = (uint)in[4] << 0x1c | *out;
          *prev = *out + *prev;
          *out = *prev;
          local_c = 5;
        }
      }
    }
  }
  return local_c;
}