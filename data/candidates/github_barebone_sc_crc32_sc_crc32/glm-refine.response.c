uint32_t __cdecl sc_crc32(uint32_t initial_crc, const void *buffer, size_t length)
{
    return crc32_sw_le(initial_crc, buffer, length);
}