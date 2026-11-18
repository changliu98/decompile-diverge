void __cdecl bit_array_mul_uint64(BIT_ARRAY *bitarr, uint64_t multiplier)
{
  bit_index_t i; // [rsp+8h] [rbp-18h]

  if ( bitarr->num_of_bits && multiplier != 1 )
  {
    if ( multiplier )
    {
      for ( i = bitarr->num_of_bits; i; --i )
      {
        if ( ((bitarr->words[(i - 1) >> 6] >> ((i - 1) & 0x3F)) & 1) != 0 )
        {
          bitarr->words[(i - 1) >> 6] &= ~(1LL << ((i - 1) & 0x3F));
          bit_array_add_word(bitarr, i - 1, multiplier);
        }
      }
    }
    else
    {
      bit_array_clear_all(bitarr);
    }
  }
}