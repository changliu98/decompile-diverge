int mustache_validate_tagname(char *tagname,size_t size)

{
  off_t off;
  size_t size_local;
  char *tagname_local;
  int local_c;
  
  if ((size == 1) && (*tagname == '.')) {
    local_c = 0;
  }
  else if ((*tagname == '.') || (tagname[size - 1] == '.')) {
    local_c = -1;
  }
  else {
    for (off = 0; (ulong)off < size; off = off + 1) {
      if ((((tagname[off] == ' ') || (tagname[off] == '\t')) || (tagname[off] == '\v')) ||
         (tagname[off] == '\f')) {
        return -1;
      }
      if (((tagname[off] == '.') && (off + 1U < size)) && (tagname[off + 1] == '.')) {
        return -1;
      }
    }
    local_c = 0;
  }
  return local_c;
}