int __cdecl archive_string_append_from_wcs(archive_string *as, const wchar_t *w, size_t len)
{
  mbstate_t shift_state;
  char *p, *end;
  int ret_val = 0;
  int n;

  memset(&shift_state, 0, sizeof(shift_state));

  // Ensure the archive string has enough space for the worst-case scenario
  if (!archive_string_ensure(as, len + as->length + 1))
    return -1;

  p = &as->s[as->length];
  end = &as->s[as->buffer_length] - __ctype_get_mb_cur_max() - 1;

  // Loop until we've processed all characters or hit a null-terminator
  while (len != 0 && *w != L'\0')
  {
    // If the write pointer is reaching the safe boundary, reallocate
    if (p >= end)
    {
      as->length = p - as->s;
      as->s[as->length] = 0;
      
      // Double the remaining length to avoid frequent reallocations
      if (!archive_string_ensure(as, 2 * len + as->length + 1))
        return -1;
        
      p = &as->s[as->length];
      end = &as->s[as->buffer_length] - __ctype_get_mb_cur_max() - 1;
    }

    // Convert wide character to multibyte sequence
    n = wcrtomb(p, *w++, &shift_state);
    
    if (n == -1)
    {
      // errno 84 is EILSEQ (Illegal byte sequence)
      if (errno != EILSEQ)
      {
        ret_val = -1;
        break;
      }
      
      // Replace invalid character with '?' (ASCII 63)
      *p++ = '?';
      ret_val = -1;
    }
    else
    {
      p += n;
    }
    
    --len;
  }

  as->length = p - as->s;
  as->s[as->length] = 0;
  
  return ret_val;
}