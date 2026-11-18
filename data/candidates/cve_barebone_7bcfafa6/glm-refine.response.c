char *__cdecl url_canonize2(
        char *d,
        const char *const s,
        size_t n,
        unsigned int syn33,
        unsigned int m32,
        unsigned int m64,
        unsigned int m96)
{
  char *da = d;
  size_t i = 0;

  // If source and destination are the same, skip over any non-percent characters
  // to avoid redundant copying until the first percent-encoded sequence is found.
  if (d == s)
  {
    while (i < n && s[i] && s[i] != '%')
    {
      ++da;
      ++i;
    }
  }

  // Main parsing loop
  while (i < n && s[i])
  {
    unsigned char c = s[i];

    if (c == '%')
    {
      unsigned char h1 = s[i + 1];
      unsigned char h2 = s[i + 2];

      // Validate that both characters following '%' are valid hex digits
      if (!IS_HEX(h1) || !IS_HEX(h2))
      {
        *da = 0;
        return 0LL;
      }

      // Convert hex characters to their numeric values
      unsigned char v1 = (h1 >= 'a') ? 87 : ((h1 >= 'A') ? 55 : 48);
      unsigned char v2 = (h2 >= 'a') ? 87 : ((h2 >= 'A') ? 55 : 48);
      unsigned char ca = (16 * (h1 - v1)) | (h2 - v2);

      // Determine if the decoded character should be kept as a literal
      // or if it must be re-encoded back to its uppercase percent-encoded form.
      bool keep_literal = false;
      if (ca <= 0x20 || ca >= 0x7F)
      {
        keep_literal = true;
      }
      else
      {
        unsigned int mask_check;
        if (ca >= 0x60)
          mask_check = (1 << (127 - ca)) & m96;
        else if (ca >= 0x40)
          mask_check = (1 << (95 - ca)) & m64;
        else
          mask_check = (1 << (63 - ca)) & m32;

        if (mask_check)
          keep_literal = true;
      }

      if (keep_literal)
      {
        // Re-encode using uppercase hex digits
        if (h1 >= 'a') h1 -= 32; // Convert to uppercase
        if (h2 >= 'a') h2 -= 32; // Convert to uppercase
        
        *da = '%';
        da[1] = h1;
        da[2] = h2;
        da += 2;
        i += 2;
      }
      else
      {
        // Store the decoded literal character
        *da = ca;
        i += 2;
      }
    }
    else
    {
      // Check if the character is allowed by the syn33 bitmask
      if (((1 << (c - 33)) & syn33) == 0)
      {
        // If not explicitly allowed, check if it falls in the unprintable/extended range
        if (c <= 0x20 || c >= 0x7F)
          return 0LL;

        // Check against the m32, m64, m96 bitmasks
        unsigned int mask_check;
        if (c >= 0x60)
          mask_check = (1 << (127 - c)) & m96;
        else if (c >= 0x40)
          mask_check = (1 << (95 - c)) & m64;
        else
          mask_check = (1 << (63 - c)) & m32;

        if (mask_check)
          return 0LL;
      }
      
      // Store the character
      *da = c;
    }
    
    ++da;
    ++i;
  }

  *da = 0;
  return da;
}