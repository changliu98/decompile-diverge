int get_opcode(const uint8_t *addr, uint32_t *opcode) 
{
    if (*addr == 0x0F) 
    {
        // Read the 2-byte opcode (little-endian: e.g., 0x0F 0x85 -> 0x850F)
        *opcode = *(const uint16_t *)addr;
        return 2;
    } 
    else 
    {
        // Read the 1-byte opcode
        *opcode = *addr;
        return 1;
    }
}