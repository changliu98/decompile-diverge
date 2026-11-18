uint32_t SCC_read(SCC *scc_instance, uint32_t address)
{
    // Handle special case for SCC type 1 at specific address range
    if ((scc_instance->type == 1) && ((address & 0xfffe) == 0xbffe)) {
        return scc_instance->base_adr >> 8 & 0x20;
    }
    // Return 0 if address is below the SCC's base address
    if (address < scc_instance->base_adr) {
        return 0;
    }
    // Calculate offset from base address
    uint32_t offset = address - scc_instance->base_adr;
    // Handle mode register read at offset 0
    if (offset == 0) {
        return scc_instance->mode == 0 ? 0x3f : 0x80;
    }
    // Return 0 if SCC is inactive or address is out of valid range
    if (((scc_instance->active == 0) || (offset < 0x800)) || (0x8ff < offset)) {
        return 0;
    }
    // Read from standard mode if SCC type is 0
    if (scc_instance->type == 0) {
        return read_standard(scc_instance, offset);
    }
    // Read from standard or enhanced mode based on SCC mode if type is 1
    if (scc_instance->type == 1) {
        return scc_instance->mode == 0 ? read_standard(scc_instance, offset) : read_enhanced(scc_instance, offset);
    }
    // Default return value for unknown types
    return 0;
}