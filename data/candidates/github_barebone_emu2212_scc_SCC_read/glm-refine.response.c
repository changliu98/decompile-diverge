uint32_t __cdecl SCC_read(SCC *scc, uint32_t adr)
{
  // Special case: Check for a specific address pattern when type is 1
  if (scc->type == 1 && (adr & 0xFFFE) == 0xBFFE)
    return (scc->base_adr >> 8) & 0x20;

  // Return 0 if the requested address is below the base address
  if (adr < scc->base_adr)
    return 0;

  uint32_t offset = adr - scc->base_adr;

  // If offset is 0, return a status byte based on the mode
  if (offset == 0)
    return scc->mode ? 0x80 : 0x3F;

  // For non-zero offsets, only process if the SCC is active and the offset 
  // falls within the 0x800 - 0x8FF range
  if (scc->active && offset >= 0x800 && offset <= 0x8FF)
  {
    if (scc->type == 0)
      return read_standard(scc, offset);
      
    if (scc->type == 1)
    {
      if (scc->mode)
        return read_enhanced(scc, offset);
        
      return read_standard(scc, offset);
    }
  }

  // Default return for unhandled addresses or unsupported types
  return 0;
}