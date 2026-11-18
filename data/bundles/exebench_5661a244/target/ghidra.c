size_t FAT_parse_directory(char *directory,size_t dirlen,size_t *startpos,size_t *endpos)

{
  size_t *endpos_local;
  size_t *startpos_local;
  size_t dirlen_local;
  char *directory_local;
  size_t local_10;
  
  while ((*startpos < dirlen && (directory[*startpos] != '\\'))) {
    *startpos = *startpos + 1;
  }
  if (*startpos == dirlen) {
    local_10 = 0;
  }
  else {
    *startpos = *startpos + 1;
    *endpos = *startpos + 1;
    while ((*endpos < dirlen && (directory[*endpos] != '\\'))) {
      *endpos = *endpos + 1;
    }
    local_10 = *endpos - *startpos;
  }
  return local_10;
}