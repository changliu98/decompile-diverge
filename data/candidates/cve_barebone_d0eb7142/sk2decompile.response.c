MOBI_RET mobi_search_links_kf7(MOBILink *link, unsigned char *start,
                               unsigned char *end) {
  if (link == NULL) {
    return 2;
  }
  link->start = NULL;
  link->end = NULL;
  link->href[0] = '\0';
  if (start == NULL || end == NULL) {
    return 2;
  }
  const unsigned char *filepos = (unsigned char *)"filepos=";
  const unsigned char *recindex = (unsigned char *)"recindex=";
  size_t filepos_len = strlen((const char *)filepos);
  size_t recindex_len = strlen((const char *)recindex);
  size_t max_len = filepos_len > recindex_len ? filepos_len : recindex_len;
  if (start + max_len > end) {
    return 0;
  }
  unsigned char *p = start;
  unsigned char last_char = '<';
  while (p <= end) {
    if (*p == '<' || *p == '>') {
      last_char = *p;
    }
    if (p + max_len <= end) {
      if (!memcmp(p, filepos, filepos_len) || !memcmp(p, recindex, recindex_len))
      {
        if (last_char == '<') {
          while (p >= start && !isspace(*p) && *p != '<') {
            p--;
          }
          p++;
          link->end = p;
          int i = 0;
          while (p <= end && !isspace(*p) && *p != '>' && i < 150) {
            link->href[i++] = *p++;
          }
          if (p[-1] == '/' && p[0] == '>') {
            p--;
            i--;
          }
          link->start = p;
          link->href[i] = '\0';
          return 0;
        }
      }
    }
    p++;
  }
  return 0;
}