static int do_read(void *buf, void *addr, unsigned long size)
{
  unsigned char *p = (uint8_t *)addr;
  unsigned char *end = p + size;
  unsigned char *b = (uint8_t *)buf;
  unsigned long n = 0;
  struct rom *rom;
  for (rom = roms; rom != ((void *)0); rom = rom->next) {
    if (rom->fw_file == ((void *)0) && rom->mr == ((void *)0)) {
      if (rom->addr <= p && p < rom->addr + rom->romsize) {
        if (rom->addr > end)
          break;
        p = b + (rom->addr - p);
        n = rom->datasize;
        if (p + n > b + size)
          n = p - b;
        if (n)
          rom_read(p, rom->data, n);
        if (rom->romsize > rom->datasize) {
          p += n;
          n = rom->romsize - rom->datasize;
          if (p + n > b + size)
            n = b - p;
          if (n)
            rom_read_fill(p, 0, n);
        }
      }
    }
  }
  return p - b;
}