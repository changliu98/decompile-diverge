unsigned char BS_ReadByte(struct GF_BitStream *bs)
{
  struct GF_BitStream *this = bs;
  if (this->bsmode == GF_BITSTREAM_READ)
  {
    if (this->position >= this->size)
    {
      if (this->EndOfStream != (void *)0)
        this->EndOfStream (this->par);
      if (this->overflow_state == 0)
        this->overflow_state = 1;
      return (0);
    }
    else
    {
      unsigned char res = this->original[this->position++];
      if (this->remove_emul_prevention_byte)
      {
        if (this->nb_zeros == 2 && res == 0x03
          && this->position < this->size
          && this->original[this->position] < 0x04)
        {
          this->nb_zeros = 0;
          res = this->original[this->position++];
        }
        if (res == 0)
          this->nb_zeros++;
        else
          this->nb_zeros = 0;
      }
      return (res);
    }
  }
  else
  {
    if (this->cache_write)
      BS_WriteCache (this);
    if (BS_GetBit (this->stream))
    {
      if (this->cache_read)
        return (BS_ReadCache (this));
      else
      {
        if (this->EndOfStream != (void *)0)
          this->EndOfStream (this->par);
        if (this->overflow_state == 0)
          this->overflow_state = 1;
        return (0);
      }
    }
    else
    {
      unsigned char res;
      unsigned char eos = GF_FALSE;
      if (this->position > this->size)
        __error__ ("bs->position<=bs->size", "/work/harness.c", 182, "unsigned char BS_ReadByte(struct GF_BitStream *bs)");
      this->position++;
      res = BS_ReadBit (this, &eos);
      if (eos)
      {
        if (this->EndOfStream != (void *)0)
          this->EndOfStream (this->par);
        if (this->overflow_state == 0)
          this->overflow_state = 1;
        if (this->position > (this->size + 1))
          __error__ ("bs->position <= 1+bs->size", "/work/harness.c", 212, "unsigned char BS_ReadByte(struct GF_BitStream *bs)");
        return (0);
      }
      if (this->remove_emul_prevention_byte)
      {
        if (this->nb_zeros == 2 && res == 0x03
          && this->position < this->size
          && (res = BS_ReadBit (this, &eos)) < 0x04)
        {
          this->nb_zeros = 0;
          res = BS_ReadBit (this, &eos);
        }
        if (res == 0)
          this->nb_zeros++;
        else
          this->nb_zeros = 0;
      }
      return (res);
    }
  }
}