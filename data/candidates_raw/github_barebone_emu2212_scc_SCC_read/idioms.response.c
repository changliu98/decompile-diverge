unsigned int scc_read(struct scc *scc, unsigned int adr)
{
  unsigned int type;
  if (scc->type == SCC_TYPE_1 && (adr & 0xfffe) == 0xc00e)
    return (scc->base_adr & 0xff00) >> 8 & 0x20;
  if (adr < scc->base_adr)
    return 0;
  adr -= scc->base_adr;
  if (adr == 0) {
    switch (scc->mode) {
    case SCC_MODE_1:
      return 0x40 | 0x80;
    case SCC_MODE_0:
      return 0x3f;
    }
  }
  if (scc->active && adr >= 0x800 && adr < 0x900) {
    type = scc->type;
    switch (type) {
    case SCC_TYPE_1:
      if (scc->mode == SCC_MODE_1)
        return scc1_read(scc, adr);
      break;
    case SCC_TYPE_0:
      return scc0_read(scc, adr);
    }
  }
  return 0;
}