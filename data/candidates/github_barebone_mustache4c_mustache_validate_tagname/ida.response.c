int __cdecl mustache_validate_tagname(const char *tagname, size_t size)
{
  size_t off; // [rsp+0h] [rbp-20h]

  if ( size == 1 && *tagname == 46 )
    return 0;
  if ( *tagname == 46 || tagname[size - 1] == 46 )
    return -1;
  for ( off = 0LL; off < size; ++off )
  {
    if ( tagname[off] == 32 || tagname[off] == 9 || tagname[off] == 11 || tagname[off] == 12 )
      return -1;
    if ( tagname[off] == 46 && off + 1 < size && tagname[off + 1] == 46 )
      return -1;
  }
  return 0;
}