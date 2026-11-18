u8 BS_ReadByte(GF_BitStream *bs)
{
  u8 res;

  if (bs->bsmode == 0) {
    if (bs->position < bs->size) {
      res = bs->original[bs->position++];
      if (bs->remove_emul_prevention_byte != GF_FALSE) {
        if (bs->nb_zeros == 2 && res == 0x03 && bs->position < bs->size && bs->original[bs->position] < 0x04) {
          bs->nb_zeros = 0;
          res = bs->original[bs->position++];
        }
        if (res == 0x00) {
          bs->nb_zeros++;
        } else {
          bs->nb_zeros = 0;
        }
      }
      return res;
    } else {
      if (bs->EndOfStream) bs->EndOfStream(bs->par);
      if (!bs->overflow_state) bs->overflow_state = 1;
      return 0;
    }
  } else {
    Bool eos;
    if (bs->cache_write) bs_flush_write_cache(bs);

    eos = gf_feof(bs->stream);
    if (eos != GF_FALSE && bs->cache_read == NULL) {
      if (bs->EndOfStream) bs->EndOfStream(bs->par);
      if (!bs->overflow_state) bs->overflow_state = 1;
      do { if (!(bs->position <= 1+bs->size)) __assert_fail("bs->position <= 1+bs->size", "/work/harness.c", 212, "u8 BS_ReadByte(GF_BitStream *)"); } while (0);
      return 0;
    }

    do { if (!(bs->position<=bs->size)) __assert_fail("bs->position<=bs->size", "/work/harness.c", 182, "u8 BS_ReadByte(GF_BitStream *)"); } while (0);
    bs->position++;
    res = gf_bs_load_byte(bs, &eos);
    if (eos != GF_FALSE) {
      if (bs->EndOfStream) bs->EndOfStream(bs->par);
      if (!bs->overflow_state) bs->overflow_state = 1;
      do { if (!(bs->position <= 1+bs->size)) __assert_fail("bs->position <= 1+bs->size", "/work/harness.c", 212, "u8 BS_ReadByte(GF_BitStream *)"); } while (0);
      return 0;
    }

    if (bs->remove_emul_prevention_byte != GF_FALSE) {
      if (bs->nb_zeros == 2 && res == 0x03 && bs->position < bs->size) {
        u8 tmp = gf_bs_load_byte(bs, &eos);
        if (tmp < 0x04) {
          bs->nb_zeros = 0;
          bs->position++;
          res = tmp;
        } else {
          gf_bs_seek(bs, bs->position);
        }
      }
      if (res == 0x00) {
        bs->nb_zeros++;
      } else {
        bs->nb_zeros = 0;
      }
    }
    return res;
  }
}