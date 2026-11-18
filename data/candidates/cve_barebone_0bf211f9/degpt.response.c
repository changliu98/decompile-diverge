int smacker_decode_tree(BitstreamContext *bc,HuffContext *hc,uint32_t prefix,int length)

{
  uint uVar1;
  uint32_t uVar2;
  int length_00;
  int r;
  int length_local;
  uint32_t prefix_local;
  HuffContext *hc_local;
  BitstreamContext *bc_local;
  int local_c;
  
  uVar1 = bitstream_read_bit(bc);
  if (uVar1 == 0) {
    if (hc->current < 0x100) {
      if (length == 0) {
        hc->bits[hc->current] = 0;
        hc->lengths[hc->current] = 0;
      }
      else {
        hc->bits[hc->current] = prefix;
        hc->lengths[hc->current] = length;
      }
      uVar2 = bitstream_read(bc,8);
      hc->values[hc->current] = uVar2;
      hc->current = hc->current + 1;
      if (hc->maxlength < length) {
        hc->maxlength = length;
      }
      local_c = 0;
    }
    else {
      av_log((void *)0x0,0x10,"Tree size exceeded!\n");
      local_c = -0x41444e49;
    }
  }
  else {
    length_00 = length + 1;
    local_c = smacker_decode_tree(bc,hc,prefix,length_00);
    if (local_c == 0) {
      local_c = smacker_decode_tree(bc,hc,prefix | 1 << ((char)length_00 - 1U & 0x1f),length_00);
    }
  }
  return local_c;
}