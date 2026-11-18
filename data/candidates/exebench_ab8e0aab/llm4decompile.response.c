void _crc32_final(uint32_t *crc)
{
    *crc = *crc ^ 0xffffffff;
}