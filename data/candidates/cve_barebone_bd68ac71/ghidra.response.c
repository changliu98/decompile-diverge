u8 BS_ReadByte(GF_BitStream *bs)

{
  u64 uVar1;
  byte bVar2;
  u8 next;
  Bool loc_eos;
  u8 res_1;
  u8 res;
  Bool is_eos;
  GF_BitStream *bs_local;
  u8 local_9;
  
  bs_local = bs;
  if (bs->bsmode == 0) {
    if (bs->position < bs->size) {
      uVar1 = bs->position;
      bs->position = uVar1 + 1;
      res = bs->original[uVar1];
      if (bs->remove_emul_prevention_byte != GF_FALSE) {
        if (((bs->nb_zeros == 2) && (res == '\x03')) &&
           ((bs->position < bs->size && (bs->original[bs->position] < '\x04')))) {
          bs->nb_zeros = 0;
          uVar1 = bs->position;
          bs->position = uVar1 + 1;
          res = bs->original[uVar1];
        }
        if (res == '\0') {
          bs->nb_zeros = bs->nb_zeros + 1;
        }
        else {
          bs->nb_zeros = 0;
        }
      }
      local_9 = res;
    }
    else {
      if (bs->EndOfStream != (_func_void_void_ptr *)0x0) {
        (*bs->EndOfStream)(bs->par);
      }
      if (bs_local->overflow_state == 0) {
        bs_local->overflow_state = 1;
      }
      local_9 = '\0';
    }
  }
  else {
    if (bs->cache_write != (char *)0x0) {
      bs_flush_write_cache(bs);
    }
    is_eos = gf_feof(bs_local->stream);
    if ((is_eos == GF_FALSE) || (bs_local->cache_read != (u8 *)0x0)) {
      loc_eos = GF_FALSE;
      if (bs_local->size < bs_local->position) {
                    /* WARNING: Subroutine does not return */
        __assert_fail("bs->position<=bs->size","/work/harness.c",0xb6,
                      "u8 BS_ReadByte(GF_BitStream *)");
      }
      bs_local->position = bs_local->position + 1;
      res_1 = gf_bs_load_byte(bs_local,&loc_eos);
      if (loc_eos == GF_FALSE) {
        if (bs_local->remove_emul_prevention_byte != GF_FALSE) {
          if (((bs_local->nb_zeros == 2) && (res_1 == '\x03')) &&
             (bs_local->position < bs_local->size)) {
            bVar2 = gf_bs_load_byte(bs_local,&loc_eos);
            if (bVar2 < 4) {
              bs_local->nb_zeros = 0;
              bs_local->position = bs_local->position + 1;
              res_1 = bVar2;
            }
            else {
              gf_bs_seek(bs_local,bs_local->position);
            }
          }
          if (res_1 == '\0') {
            bs_local->nb_zeros = bs_local->nb_zeros + 1;
          }
          else {
            bs_local->nb_zeros = 0;
          }
        }
        return res_1;
      }
    }
    if ((bs_local->EndOfStream != (_func_void_void_ptr *)0x0) &&
       ((*bs_local->EndOfStream)(bs_local->par), bs_local->overflow_state == 0)) {
      bs_local->overflow_state = 1;
    }
    if (bs_local->size + 1 < bs_local->position) {
                    /* WARNING: Subroutine does not return */
      __assert_fail("bs->position <= 1+bs->size","/work/harness.c",0xd4,
                    "u8 BS_ReadByte(GF_BitStream *)");
    }
    local_9 = '\0';
  }
  return local_9;
}