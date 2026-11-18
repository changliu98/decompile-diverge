void _crc32_final(uint *crc)

{
  uint *crc_local;
  
  *crc = *crc ^ 0xffffffff;
  return;
}