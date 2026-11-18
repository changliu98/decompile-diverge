int rom_copy(unsigned char *buf, off_t start, int len) {
  off_t end = start + len;
  unsigned char *p = buf;
  int size = 0;
  struct rom *rom;
  for (rom = rom_head; rom; rom = rom->link.next) {
    if (rom->removed || rom->readonly) continue;
    if (rom->start + rom->size < start) continue;
    if (rom->start > end) break;
    p = buf + (rom->start - start);
    size = rom->size;
    if (p + size > buf + len) size = start - rom->start;
    if (size) memcpy(p, rom->data, size);
    if (rom->size < rom->start) {
      p += size;
      size = rom->start - rom->size;
      if (p + size > buf + len) size = buf - p;
      if (size) memset(p, 0, size);
    }
  }
  return p - buf + size;
}