void __cdecl ck_decrypt(char *s)
{
  while (*s)
  {
    // Check if the current character is NOT 'p' (0x70), '\\' (0x5C), or 'S' (0x53)
    if (*s != 'p' && *s != '\\' && *s != 'S')
    {
      // XOR the character with 0x0F to transform it
      *s ^= 0x0F;
    }
    ++s;
  }
}