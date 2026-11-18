int FAT_parse_directory(char *directory, unsigned long dirlen, unsigned long *startpos, unsigned long *endpos)
{
  for ( ; *startpos < dirlen && directory[*startpos] != '\\'; ++*startpos);
  if ( *startpos == dirlen )
    return 0;
  for ( ++*startpos, ++*endpos; *endpos < dirlen && directory[*endpos] != '\\'; ++*endpos);
  return *endpos - *startpos;
}