void __cdecl compute_accelerated_huffman(Codebook *c)
{
  unsigned int v1; // [rsp+4h] [rbp-1Ch]
  int sorted_entries; // [rsp+8h] [rbp-18h]
  uint32 z; // [rsp+Ch] [rbp-14h]
  int len; // [rsp+10h] [rbp-10h]
  int i; // [rsp+14h] [rbp-Ch]
  int ia; // [rsp+14h] [rbp-Ch]

  for ( i = 0; i < 1024; ++i )
    c->fast_huffman[i] = -1;
  if ( c->sparse )
    sorted_entries = c->sorted_entries;
  else
    sorted_entries = c->entries;
  len = sorted_entries;
  if ( sorted_entries > 0x7FFF )
    len = 0x7FFF;
  for ( ia = 0; ia < len; ++ia )
  {
    if ( c->codeword_lengths[ia] <= 0xAu )
    {
      if ( c->sparse )
        v1 = bit_reverse(c->sorted_codewords[ia]);
      else
        v1 = c->codewords[ia];
      for ( z = v1; z < 0x400; z += 1 << c->codeword_lengths[ia] )
        c->fast_huffman[z] = ia;
    }
  }
}