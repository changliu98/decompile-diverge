char *__cdecl func0(const char *text)
{
  size_t length = strlen(text);
  char *result = (char *)malloc(2 * length + 1);
  size_t j = 0;

  for (size_t i = 0; i < length; ++i)
  {
    // Fetch the character type flags for the current, previous, and next characters.
    // The glibc __ctype_b_loc() returns a pointer to a table of 16-bit flags.
    const unsigned short *ctype = *__ctype_b_loc();
    unsigned short cur_flags  = ctype[(unsigned char)text[i]];
    unsigned short prev_flags = (i > 0) ? ctype[(unsigned char)text[i - 1]] : 0;
    unsigned short next_flags = ctype[(unsigned char)text[i + 1]];

    // glibc character class bitmasks:
    // 0x100 = _ISupper (Uppercase)
    // 0x200 = _ISlower (Lowercase)
    // 0x800 = _ISdigit (Digit)

    // Condition 1: Current char is uppercase, preceded by a lowercase letter or digit.
    bool cond1 = (i > 0) && 
                 ((cur_flags & 0x100) != 0) && 
                 (((prev_flags & 0x200) != 0) || ((prev_flags & 0x800) != 0));

    // Condition 2: Current char is uppercase, preceded by an uppercase letter, 
    // and followed by a lowercase letter (e.g., "XMLParser" -> "xml_parser").
    bool cond2 = (i > 0) && 
                 ((cur_flags & 0x100) != 0) && 
                 ((prev_flags & 0x100) != 0) && 
                 ((next_flags & 0x200) != 0);

    if (cond1 || cond2)
    {
      result[j++] = '_';
      result[j++] = tolower(text[i]);
    }
    else
    {
      result[j++] = tolower(text[i]);
    }
  }
  
  result[j] = '\0';
  return result;
}