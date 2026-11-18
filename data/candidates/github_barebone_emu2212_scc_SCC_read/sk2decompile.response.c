unsigned char SCC_read(SCC *scc, unsigned int addr) {
  unsigned int offset;
  if (scc->mode == 1 && (addr & 0xfffe) == 0xc006) {
    return (scc->base >> 8) & 0x20;
  }
  if (addr < scc->base) return 0;
  offset = addr - scc->base;
  if (offset == 0) {
    if (scc->enhanced) return 0x80;
    return 0x3f;
  }
  if (scc->enabled && offset >= 0x800 && offset < 0x800 + 0x80) {
    switch (scc->mode) {
      case 0:
        return read_standard(scc, offset);
      case 1:
        if (scc->enhanced) return read_enhanced(scc, offset);
        return read_standard(scc, offset);
    }
  }
  return 0;
}