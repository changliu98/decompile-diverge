void _crc32_final(uint *crc)
{
  *crc = *crc ^ 0xffffffff;
}