static int do_bid_note(struct magic_set *ms, unsigned char *buf, unsigned int type, int swap, unsigned int namesz, unsigned int descsz, unsigned long noff, unsigned long doff, int *flags)
{
  char desc[20];
  unsigned int i;
  if (namesz != 4 ||
      strncasecmp((char *)(buf + noff), s2, sizeof s2) != 0 ||
      type != 3)
    return 0;
  *flags |= 16;
  switch (descsz) {
  case 8:
    if (magic_set_add_string(ms, ", BuildID[%s]=", "xxHash") == -1)
      return 1;
    break;
  case 16:
    if (magic_set_add_string(ms, ", BuildID[%s]=", "md5/uuid") == -1)
      return 1;
    break;
  case 20:
    if (magic_set_add_string(ms, ", BuildID[%s]=", "sha1") == -1)
      return 1;
    break;
  default:
    if (magic_set_add_string(ms, ", BuildID[%s]=", "unknown") == -1)
      return 1;
    break;
  }
  hextostr(desc, (char *)(buf + doff), descsz);
  for (i = 0; i < descsz; i++)
    if (magic_set_add_string(ms, "%02x", desc[i]) == -1)
      return 1;
  return 1;
}