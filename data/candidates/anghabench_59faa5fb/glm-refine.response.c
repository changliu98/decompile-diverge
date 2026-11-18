void __cdecl scsi_sanitize_inquiry_string(unsigned char *s, int len)
{
  int terminated = 0;

  while (len > 0)
  {
    // If we encounter a null terminator, mark the string as terminated
    if (*s == '\0')
      terminated = 1;

    // If the string was already terminated, or the current character is 
    // outside the standard printable ASCII range (0x20 - 0x7E), replace it with a space.
    if (terminated || *s < 0x20 || *s > 0x7E)
      *s = ' ';

    ++s;
    --len;
  }
}