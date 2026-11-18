uint32_t
SCC_read (SCC * scc, uint32_t adr)
{
  if( scc->type == SCC_ENHANCED && (adr&0xFFFE) == 0xBFFE ) 
    return (scc->base_adr>>8)&0x20;
  
  if( adr < scc->base_adr ) return 0;
  adr -= scc->base_adr;
  
  if( adr == 0 ) 
  {
    if(scc->mode) return 0x80; else return 0x3F;
  }

  if(!scc->active||adr<0x800||0x8FF<adr) return 0;

  switch (scc->type) 
  {
  case SCC_STANDARD:
      return read_standard (scc, adr);
    break;
  case SCC_ENHANCED:
    if(!scc->mode)
      return read_standard (scc, adr);
    else 
      return read_enhanced (scc, adr);
    break;
  default:
    break;
  }

  return 0;
}