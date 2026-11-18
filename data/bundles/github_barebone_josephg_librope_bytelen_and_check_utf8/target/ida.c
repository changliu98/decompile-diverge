ssize_t __cdecl bytelen_and_check_utf8(const uint8_t *str)
{
  size_t size; // [rsp+0h] [rbp-20h]
  size_t sizea; // [rsp+0h] [rbp-20h]
  uint8_t *p; // [rsp+8h] [rbp-18h]

  p = (uint8_t *)str;
  while ( *p )
  {
    size = codepoint_size(*p);
    if ( size == -1LL )
      return -1LL;
    ++p;
    for ( sizea = size - 1; sizea; --sizea )
    {
      if ( (*p & 0xC0) != 128 )
        return -1LL;
      ++p;
    }
  }
  return p - str;
}