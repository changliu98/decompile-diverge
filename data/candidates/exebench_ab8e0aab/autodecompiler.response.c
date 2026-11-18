void _crc32_final(CRC16 *crc)
{
 crc->checksum = ~crc->checksum;
}