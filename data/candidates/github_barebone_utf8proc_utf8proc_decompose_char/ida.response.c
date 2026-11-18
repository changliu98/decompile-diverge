utf8proc_ssize_t __cdecl utf8proc_decompose_char(
        utf8proc_int32_t uc,
        utf8proc_int32_t *dst,
        utf8proc_ssize_t bufsize,
        utf8proc_option_t options,
        int *last_boundclass)
{
  utf8proc_int32_t hangul_sindex; // [rsp+10h] [rbp-40h]
  utf8proc_propval_t category; // [rsp+16h] [rbp-3Ah]
  const utf8proc_property_t *property; // [rsp+18h] [rbp-38h]

  if ( (unsigned int)uc >= 0x110000 )
    return -4LL;
  property = unsafe_get_property(uc);
  category = property->category;
  hangul_sindex = uc - 44032;
  if ( (options & 0x18) != 0 && (unsigned int)hangul_sindex <= 0x2BA3 )
  {
    if ( bufsize >= 1 )
    {
      *dst = hangul_sindex / 588 + 4352;
      if ( bufsize >= 2 )
        dst[1] = hangul_sindex % 588 / 28 + 4449;
    }
    if ( hangul_sindex % 28 )
    {
      if ( bufsize >= 3 )
        dst[2] = hangul_sindex % 28 + 4519;
      return 3LL;
    }
    else
    {
      return 2LL;
    }
  }
  else if ( (options & 0x40) == 0 || category )
  {
    if ( (options & 0x20) != 0 && ((*(_DWORD *)((char *)property + 18) >> 18) & 1) != 0 )
    {
      return 0LL;
    }
    else if ( (options & 0x4000) == 0 || category )
    {
      if ( (options & 0x1000) != 0 )
      {
        if ( category == 23 )
          return utf8proc_decompose_char(32, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
        if ( uc == 8216 || uc == 8217 || uc == 700 || uc == 712 )
          return utf8proc_decompose_char(39, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
        if ( category == 13 || uc == 8722 )
          return utf8proc_decompose_char(45, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
        switch ( uc )
        {
          case 8260:
          case 8725:
            return utf8proc_decompose_char(47, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
          case 8758:
            return utf8proc_decompose_char(58, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
          case 8249:
          case 9001:
          case 12296:
            return utf8proc_decompose_char(60, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
          case 8250:
          case 9002:
          case 12297:
            return utf8proc_decompose_char(62, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
          case 8726:
            return utf8proc_decompose_char(92, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
          case 708:
          case 710:
          case 8248:
          case 8963:
            return utf8proc_decompose_char(94, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
        }
        if ( category == 12 || uc == 717 )
          return utf8proc_decompose_char(95, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
        switch ( uc )
        {
          case 715:
            return utf8proc_decompose_char(96, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
          case 8739:
            return utf8proc_decompose_char(
                     124,
                     dst,
                     bufsize,
                     (utf8proc_option_t)(options & 0xFFFFEFFF),
                     last_boundclass);
          case 8764:
            return utf8proc_decompose_char(
                     126,
                     dst,
                     bufsize,
                     (utf8proc_option_t)(options & 0xFFFFEFFF),
                     last_boundclass);
        }
        if ( (options & 0x80) != 0 && (options & 0x100) != 0 && (category == 24 || category == 25) )
          return utf8proc_decompose_char(10, dst, bufsize, (utf8proc_option_t)(options & 0xFFFFEFFF), last_boundclass);
      }
      if ( (options & 0x2000) != 0 && (category == 6 || category == 7 || category == 8) )
      {
        return 0LL;
      }
      else if ( (options & 0x400) == 0 || property->casefold_seqindex == 0xFFFF )
      {
        if ( (options & 0x18) == 0 || property->decomp_seqindex == 0xFFFF || property->decomp_type && (options & 4) == 0 )
        {
          if ( (options & 0x800) != 0
            && grapheme_break_extended(
                 0,
                 HIBYTE(*(_DWORD *)((char *)property + 18)) & 0x3F,
                 0,
                 *(_DWORD *)((char *)property + 18) >> 30,
                 last_boundclass) )
          {
            if ( bufsize >= 1 )
              *dst = -1;
            if ( bufsize >= 2 )
              dst[1] = uc;
            return 2LL;
          }
          else
          {
            if ( bufsize >= 1 )
              *dst = uc;
            return 1LL;
          }
        }
        else
        {
          return seqindex_write_char_decomposed(property->decomp_seqindex, dst, bufsize, options, last_boundclass);
        }
      }
      else
      {
        return seqindex_write_char_decomposed(property->casefold_seqindex, dst, bufsize, options, last_boundclass);
      }
    }
    else
    {
      return 0LL;
    }
  }
  else
  {
    return -4LL;
  }
}