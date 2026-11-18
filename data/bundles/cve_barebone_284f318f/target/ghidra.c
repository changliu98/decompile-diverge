int rom_copy(uint8_t *dest,hwaddr addr,size_t size)

{
  Rom *rom;
  size_t l;
  uint8_t *d;
  uint8_t *s;
  hwaddr end;
  size_t size_local;
  hwaddr addr_local;
  uint8_t *dest_local;
  
  l = 0;
  d = dest;
  for (rom = roms.tqh_first; rom != (Rom *)0x0; rom = (rom->next).tqe_next) {
    if (((rom->fw_file == (char *)0x0) && (rom->mr == (MemoryRegion *)0x0)) &&
       (addr <= rom->addr + rom->romsize)) {
      if (addr + size < rom->addr) break;
      d = dest + (rom->addr - addr);
      l = rom->datasize;
      if (dest + size < d + l) {
        l = (long)dest - (long)d;
      }
      if (l != 0) {
        memcpy(d,rom->data,l);
      }
      if (rom->datasize < rom->romsize) {
        d = d + l;
        l = rom->romsize - rom->datasize;
        if (dest + size < d + l) {
          l = (long)dest - (long)d;
        }
        if (l != 0) {
          memset(d,0,l);
        }
      }
    }
  }
  return ((int)d + (int)l) - (int)dest;
}