void __cdecl crc32_final(unsigned int *crc)
{
  *crc = ~*crc;
}