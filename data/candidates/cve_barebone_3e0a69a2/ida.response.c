void __cdecl read_quant_matrix_ext(MpegEncContext *s, GetBitContext *gb)
{
  uint16_t v; // [rsp+4h] [rbp-1Ch]
  int j; // [rsp+8h] [rbp-18h]
  int i; // [rsp+Ch] [rbp-14h]
  int ia; // [rsp+Ch] [rbp-14h]
  int ib; // [rsp+Ch] [rbp-14h]
  int ic; // [rsp+Ch] [rbp-14h]

  if ( get_bits1(gb) )
  {
    for ( i = 0; i < 64; ++i )
    {
      v = get_bits(gb, 8);
      j = s->idsp.idct_permutation[ff_zigzag_direct[i]];
      s->intra_matrix[s->idsp.idct_permutation[ff_zigzag_direct[i]]] = v;
      s->chroma_intra_matrix[j] = v;
    }
  }
  if ( get_bits1(gb) )
  {
    for ( ia = 0; ia < 64; ++ia )
      get_bits(gb, 8);
  }
  if ( get_bits1(gb) )
  {
    for ( ib = 0; ib < 64; ++ib )
      s->chroma_intra_matrix[s->idsp.idct_permutation[ff_zigzag_direct[ib]]] = get_bits(gb, 8);
  }
  if ( get_bits1(gb) )
  {
    for ( ic = 0; ic < 64; ++ic )
      get_bits(gb, 8);
  }
  next_start_code_studio(gb);
}