static int
rom_copy(uint32_t addr, uint32_t end, size_t len)
{
    rom_t *rom;
    char *ptr;
    long l;
    uint32_t e = end + len;
    char *p = (char *) addr;
    long c = 0;

    for (rom = roms; rom != NULL; rom = rom->next) {
 if ((rom->enabled) || (rom->shadow)) continue;
 if ((rom->addr + rom->len) < end) continue;
 if (rom->addr > e) break;
 p = (char *) (addr + (rom->addr - end));
 ptr = (char *) rom->ptr;
 c = rom->csize;
 if ((p + c) > ((char *) (addr + len)))
  c = ((char *) (addr + len)) - p;
 if (c > 0)
  memcpy(p, ptr, c);
 if (rom->len > rom->csize) {
  p += c;
  c = rom->len - rom->csize;
  if ((p + c) > ((char *) (addr + len)))
   c = ((char *) (addr + len)) - p;
  if (c > 0)
   memset(p, 0, c);
 }
    }

    return((long) (p + c) - (long) addr);
}