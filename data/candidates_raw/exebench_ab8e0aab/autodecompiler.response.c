void CRC16Invert(CRC16 *crc)
{
 crc->checksum = ~crc->checksum;
}