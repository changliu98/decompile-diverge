uint16_t get_bits(heatshrink_decoder *hsd,uint8_t count)

{
  ushort uVar1;
  int i;
  uint16_t accumulator;
  uint8_t count_local;
  heatshrink_decoder *hsd_local;
  uint16_t local_a;
  
  accumulator = 0;
  if (count < 0x10) {
    if ((hsd->input_size == 0) && ((int)(uint)hsd->bit_index < 1 << (count - 1 & 0x1f))) {
      local_a = 0xffff;
    }
    else {
      for (i = 0; i < (int)(uint)count; i = i + 1) {
        if (hsd->bit_index == '\0') {
          if (hsd->input_size == 0) {
            return 0xffff;
          }
          uVar1 = hsd->input_index;
          hsd->input_index = uVar1 + 1;
          hsd->current_byte = *(uint8_t *)((long)&hsd[1].input_size + (ulong)uVar1);
          if (hsd->input_index == hsd->input_size) {
            hsd->input_index = 0;
            hsd->input_size = 0;
          }
          hsd->bit_index = 0x80;
        }
        accumulator = accumulator << 1;
        if ((hsd->current_byte & hsd->bit_index) != 0) {
          accumulator = accumulator | 1;
        }
        hsd->bit_index = (uint8_t)((int)(uint)hsd->bit_index >> 1);
      }
      local_a = accumulator;
    }
  }
  else {
    local_a = 0xffff;
  }
  return local_a;
}