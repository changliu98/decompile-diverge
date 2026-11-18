size_t __cdecl FAT_parse_directory(const char *directory, size_t dirlen, size_t *startpos, size_t *endpos)
{
  while ( *startpos < dirlen && directory[*startpos] != 92 )
    ++*startpos;
  if ( *startpos == dirlen )
    return 0LL;
  for ( *endpos = ++*startpos + 1; *endpos < dirlen && directory[*endpos] != 92; ++*endpos )
    ;
  return *endpos - *startpos;
}