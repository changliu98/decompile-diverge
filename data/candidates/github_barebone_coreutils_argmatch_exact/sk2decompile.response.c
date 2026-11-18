static ptrdiff_t argmatch_exact(const char *arg, const char **list) {
  ptrdiff_t i;
  for (i = 0; list[i]; i++)
    if (!strcmp(list[i], arg)) return i;
  return -1;
}