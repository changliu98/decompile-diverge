uint32_t __cdecl SCC_read(SCC *scc, uint32_t adr)
{
  uint32_t type; // [rsp+8h] [rbp-18h]
  uint32_t adra; // [rsp+Ch] [rbp-14h]

  if ( scc->type == 1 && (adr & 0xFFFE) == 49150 )
    return (scc->base_adr >> 8) & 0x20;
  if ( adr < scc->base_adr )
    return 0;
  adra = adr - scc->base_adr;
  if ( adra )
  {
    if ( scc->active && adra >= 0x800 && adra <= 0x8FF )
    {
      type = scc->type;
      if ( type )
      {
        if ( type != 1 )
          return 0;
        if ( scc->mode )
          return read_enhanced(scc, adra);
      }
      return read_standard(scc, adra);
    }
    return 0;
  }
  else if ( scc->mode )
  {
    return 128;
  }
  else
  {
    return 63;
  }
}