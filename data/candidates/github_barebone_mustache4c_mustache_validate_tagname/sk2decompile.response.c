int mustache_validate_tagname(const char *tagname, size_t len) {
  size_t i;
  if (len == 1 && tagname[0] == '.') return 0;
  if (tagname[0] == '.' || tagname[len - 1] == '.') return -1;
  for (i = 0; i < len; i++) {
    if (tagname[i] == ' ' || tagname[i] == '\t' || tagname[i] == '\v' ||
        tagname[i] == '\f')
      return -1;
    if (tagname[i] == '.' && i + 1 < len && tagname[i + 1] == '.') return -1;
  }
  return 0;
}