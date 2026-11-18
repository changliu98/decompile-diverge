char __cdecl bit_array_sub_uint64(BIT_ARRAY *bitarr, uint64_t value)
{
  word_addr_t i; // [rsp+0h] [rbp-20h]
  uint64_t valuea; // [rsp+8h] [rbp-18h]

  if ( !value )
    return 1;
  if ( *bitarr->words < value )
  {
    valuea = value - *bitarr->words;
    for ( i = 1LL; ; ++i )
    {
      if ( i >= bitarr->num_of_words )
        return 0;
      if ( bitarr->words[i] )
        break;
    }
    --bitarr->words[i];
    while ( i )
      bitarr->words[i--] = -1LL;
    *bitarr->words = -1LL - valuea - 1;
    return 1;
  }
  else
  {
    *bitarr->words -= value;
    return 1;
  }
}