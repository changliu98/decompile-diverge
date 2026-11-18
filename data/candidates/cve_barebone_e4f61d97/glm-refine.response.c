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

  // In-place canonization fast-path: if source and destination buffers are the same,
  // advance the destination pointer to skip over safe characters that don't require modification.
  if (d == s)
  {
    while (s[i] && i < n && s[i] != '%')
    {
      ++da;
      ++i;
    }
  }

  // Main parsing loop
  while (s[i] && i < n)
  {
    unsigned __int8 c = s[i];

    if (c == '%')
    {
      unsigned __int8 h1 = s[i + 1];
      if (!h1)
      {
        *da = 0;
        return 0LL;
      }

      unsigned __int8 h2 = s[i + 2];
      if (!IS_HEX(h1) || !IS_HEX(h2))
      {
        *da = 0;
        return 0LL;
      }

      // Convert hex characters to their numeric values
      unsigned __int8 v1 = (h1 >= 'a') ? (h1 - 'a' + 10) : ((h1 >= 'A') ? (h1 - 'A' + 10) : (h1 - '0'));
      unsigned __int8 v2 = (h2 >= 'a') ? (h2 - 'a' + 10) : ((h2 >= 'A') ? (h2 - 'A' + 10) : (h2 - '0'));
      unsigned __int8 ca = (v1 << 4) | v2;

      // Determine if the decoded character is considered "unsafe" and must remain percent-encoded.
      // The original code uses bitmasks (m32, m64, m96) to represent unsafe characters in 3 ranges:
      // 0x21-0x3F, 0x40-0x5F, and 0x60-0x7E. Characters <= 0x20 or >= 0x7F are inherently unsafe.
      bool is_unsafe = false;
      if (ca <= 0x20 || ca >= 0x7F)
      {
        is_unsafe = true;
      }
      else if (ca >= 0x60)
      {
        if ((1 << (127 - ca)) & m96) is_unsafe = true;
      }
      else if (ca >= 0x40)
      {
        if ((1 << (95 - ca)) & m64) is_unsafe = true;
      }
      else
      {
        if ((1 << (63 - ca)) & m32) is_unsafe = true;
      }

      if (is_unsafe)
      {
        // Keep it percent-encoded, but uppercase the hex digits for canonicalization
        if (h1 >= 'a') h1 -= 32; // 'a' - 'A'
        if (h2 >= 'a') h2 -= 32;

        *da = '%';
        da[1] = h1;
        da[2] = h2;
        da += 2;
        i += 2;
      }
      else
      {
        // Safe character: decode it directly
        *da = ca;
        i += 2;
      }
    }
    else
    {
      // For non-percent-encoded characters, check if they are explicitly unsafe.
      bool is_unsafe = false;
      if (((1 << (c - 33)) & syn33) == 0)
      {
        if (c <= 0x20 || c >= 0x7F)
        {
          return 0LL;
        }
        else if (c >= 0x60)
        {
          if ((1 << (127 - c)) & m96) is_unsafe = true;
        }
        else if (c >= 0x40)
        {
          if ((1 << (95 - c)) & m64) is_unsafe = true;
        }
        else
        {
          if ((1 << (63 - c)) & m32) is_unsafe = true;
        }

        if (is_unsafe)
          return 0LL;
      }

      *da = c;
    }

    ++da;
    ++i;
  }

  *da = 0;
  return da;
}