u8 __cdecl BS_ReadByte(GF_BitStream *bs)
{
  char *original; // rax
  u64 position; // rcx
  char *v3; // rax
  u64 v4; // rcx
  u8 next; // [rsp+3h] [rbp-1Dh]
  Bool loc_eos; // [rsp+4h] [rbp-1Ch] BYREF
  u8 res_0; // [rsp+Ah] [rbp-16h]
  u8 res; // [rsp+Bh] [rbp-15h]
  Bool is_eos; // [rsp+Ch] [rbp-14h]
  GF_BitStream *bsa; // [rsp+10h] [rbp-10h]

  bsa = bs;
  if ( bs->bsmode )
  {
    if ( bsa->cache_write )
      bs_flush_write_cache(bsa);
    is_eos = gf_feof(bsa->stream);
    if ( is_eos && !bsa->cache_read )
      goto LABEL_45;
    loc_eos = GF_FALSE;
    if ( bsa->position > bsa->size )
      __assert_fail("bs->position<=bs->size", "/work/harness.c", 0xB6u, "u8 BS_ReadByte(GF_BitStream *)");
    ++bsa->position;
    res_0 = gf_bs_load_byte(bsa, &loc_eos);
    if ( loc_eos )
    {
LABEL_45:
      if ( bsa->EndOfStream )
      {
        bsa->EndOfStream(bsa->par);
        if ( !bsa->overflow_state )
          bsa->overflow_state = 1;
      }
      if ( bsa->position > bsa->size + 1 )
        __assert_fail("bs->position <= 1+bs->size", "/work/harness.c", 0xD4u, "u8 BS_ReadByte(GF_BitStream *)");
      return 0;
    }
    else
    {
      if ( bsa->remove_emul_prevention_byte )
      {
        if ( bsa->nb_zeros == 2 && res_0 == 3 && bsa->position < bsa->size )
        {
          next = gf_bs_load_byte(bsa, &loc_eos);
          if ( next >= 4u )
          {
            gf_bs_seek(bsa, bsa->position);
          }
          else
          {
            bsa->nb_zeros = 0;
            res_0 = next;
            ++bsa->position;
          }
        }
        if ( res_0 )
          bsa->nb_zeros = 0;
        else
          ++bsa->nb_zeros;
      }
      return res_0;
    }
  }
  else if ( bsa->position < bsa->size )
  {
    original = bsa->original;
    position = bsa->position;
    bsa->position = position + 1;
    res = original[position];
    if ( bsa->remove_emul_prevention_byte )
    {
      if ( bsa->nb_zeros == 2 && res == 3 && bsa->position < bsa->size && bsa->original[bsa->position] < 4 )
      {
        bsa->nb_zeros = 0;
        v3 = bsa->original;
        v4 = bsa->position;
        bsa->position = v4 + 1;
        res = v3[v4];
      }
      if ( res )
        bsa->nb_zeros = 0;
      else
        ++bsa->nb_zeros;
    }
    return res;
  }
  else
  {
    if ( bsa->EndOfStream )
      bsa->EndOfStream(bsa->par);
    if ( !bsa->overflow_state )
      bsa->overflow_state = 1;
    return 0;
  }
}