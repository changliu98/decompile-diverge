int __cdecl is_valid_ref_char(char ch_0)
{
  return (unsigned int)ch_0 > 0x20
      && ch_0 != 42
      && ch_0 != 58
      && ch_0 != 63
      && (unsigned int)(ch_0 - 91) >= 2
      && ch_0 != 94
      && ch_0 != 126;
}