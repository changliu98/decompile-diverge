char *__cdecl isis_print_id(const uint8_t *cp, int id_len)
{
  char *pos = isis_print_id_id;
  int i;

  // Format the System ID (first 6 bytes)
  for (i = 1; i <= 6; ++i)
  {
    snprintf(pos, 21 - (pos - isis_print_id_id), "%02x", *cp++);
    pos += strlen(pos);
    
    // Insert dots after the 2nd and 4th bytes
    if (i == 2 || i == 4)
      *pos++ = '.';
  }

  // Format the SEL byte if present
  if (id_len >= 7)
  {
    snprintf(pos, 21 - (pos - isis_print_id_id), ".%02x", *cp++);
    pos += strlen(pos);
  }

  // Format the extra byte if id_len is exactly 8
  if (id_len == 8)
    snprintf(pos, 21 - (pos - isis_print_id_id), "-%02x", *cp);

  return isis_print_id_id;
}