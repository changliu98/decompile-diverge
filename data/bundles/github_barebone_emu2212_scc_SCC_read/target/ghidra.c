uint32_t SCC_read(SCC *scc,uint32_t adr)

{
  uint adr_00;
  uint32_t adr_local;
  SCC *scc_local;
  uint local_c;
  
  if ((scc->type == 1) && ((adr & 0xfffe) == 0xbffe)) {
    local_c = scc->base_adr >> 8 & 0x20;
  }
  else if (adr < scc->base_adr) {
    local_c = 0;
  }
  else {
    adr_00 = adr - scc->base_adr;
    if (adr_00 == 0) {
      if (scc->mode == 0) {
        local_c = 0x3f;
      }
      else {
        local_c = 0x80;
      }
    }
    else if (((scc->active == 0) || (adr_00 < 0x800)) || (0x8ff < adr_00)) {
      local_c = 0;
    }
    else if (scc->type == 0) {
      local_c = read_standard(scc,adr_00);
    }
    else if (scc->type == 1) {
      if (scc->mode == 0) {
        local_c = read_standard(scc,adr_00);
      }
      else {
        local_c = read_enhanced(scc,adr_00);
      }
    }
    else {
      local_c = 0;
    }
  }
  return local_c;
}