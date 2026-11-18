static unsigned int SCC_read(scc_t *scc, unsigned int addr)
{
  unsigned int ret;
  int i;

  if ((scc->mode == 1) && ((addr & 0xfffe) == 0xbffe)) {
    ret = (scc->status & 0x2000) >> 8;
  } else if (addr < scc->base) {
    ret = 0;
  } else {
    addr -= scc->base;
    if (addr == 0) {
      if (scc->irq_pending) {
        ret = 0x80;
      } else {
        ret = 0x3f;
      }
    } else if (!scc->enhanced || (addr < 0x800) || (addr > 0x8ff)) {
      ret = 0;
    } else {
      i = scc->mode;
      if (i) {
        while (--i) {
          if (i == 0) {
            if (!scc->irq_pending) {
              ret = read_standard(scc, addr);
            } else {
              ret = read_enhanced(scc, addr);
            }
          } else {
            ret = 0;
          }
        }
      } else {
        ret = read_standard(scc, addr);
      }
    }
  }

  return ret;
}