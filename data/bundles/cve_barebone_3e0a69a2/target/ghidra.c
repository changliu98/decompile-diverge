void read_quant_matrix_ext(MpegEncContext *s,GetBitContext *gb)

{
  uint uVar1;
  uint uVar2;
  int v;
  int j;
  int i;
  GetBitContext *gb_local;
  MpegEncContext *s_local;
  
  uVar1 = get_bits1(gb);
  if (uVar1 != 0) {
    for (i = 0; i < 0x40; i = i + 1) {
      uVar1 = get_bits(gb,8);
      uVar2 = (uint)(s->idsp).idct_permutation[""[i]];
      s->intra_matrix[(int)uVar2] = (uint16_t)uVar1;
      s->chroma_intra_matrix[(int)uVar2] = (uint16_t)uVar1;
    }
  }
  uVar1 = get_bits1(gb);
  if (uVar1 != 0) {
    for (i = 0; i < 0x40; i = i + 1) {
      get_bits(gb,8);
    }
  }
  uVar1 = get_bits1(gb);
  if (uVar1 != 0) {
    for (i = 0; i < 0x40; i = i + 1) {
      uVar1 = get_bits(gb,8);
      s->chroma_intra_matrix[(int)(uint)(s->idsp).idct_permutation[""[i]]] = (uint16_t)uVar1;
    }
  }
  uVar1 = get_bits1(gb);
  if (uVar1 != 0) {
    for (i = 0; i < 0x40; i = i + 1) {
      get_bits(gb,8);
    }
  }
  next_start_code_studio(gb);
  return;
}