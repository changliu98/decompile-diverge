size_t __cdecl count_string(const uint8_t *raw, const uint8_t *end, int *infoout)
{
  bool is_escaped = false;
  int info = 0;
  size_t i = 1;
  size_t len = end - raw;

  // Main loop: heavily unrolled by the compiler to process 8 bytes per iteration
  while (i + 8 <= len)
  {
    // Check 8 bytes sequentially, jumping to the token handler if a special char is found
    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;

    continue; // Move to the next 8-byte chunk

  tok:
    // Token handler for special characters
    if (raw[i] == '"')
    {
      ++i;
      if (!is_escaped)
        goto LABEL_22; // End of string
      is_escaped = false;
    }
    else
    {
      if (raw[i] == '\\')
      {
        info |= STRING_HAS_ESCAPES;
        is_escaped = !is_escaped;
      }
      ++i;
    }
  }

  // Cleanup loop: process any remaining bytes (less than 8) one by one
  while (i + 1 <= len)
  {
    if (strtoksa[raw[i]])
      goto tok;
    is_escaped = false;
    ++i;
  }

LABEL_22:
  *infoout = info;
  return i;
}