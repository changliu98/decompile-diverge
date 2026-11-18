int __cdecl read_int_delta(const uint8_t *in, uint32_t *out, uint32_t *prev)
{
  *out = *in & 0x7F;
  if ( *in >= 0x80u )
  {
    *out |= (in[1] & 0x7F) << 7;
    if ( in[1] >= 0x80u )
    {
      *out |= (in[2] & 0x7F) << 14;
      if ( in[2] >= 0x80u )
      {
        *out |= (in[3] & 0x7F) << 21;
        if ( in[3] >= 0x80u )
        {
          *out |= (in[4] & 0x7F) << 28;
          *prev += *out;
          *out = *prev;
          return 5;
        }
        else
        {
          *prev += *out;
          *out = *prev;
          return 4;
        }
      }
      else
      {
        *prev += *out;
        *out = *prev;
        return 3;
      }
    }
    else
    {
      *prev += *out;
      *out = *prev;
      return 2;
    }
  }
  else
  {
    *prev += *out;
    *out = *prev;
    return 1;
  }
}