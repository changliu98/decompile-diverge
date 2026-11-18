void calculate_crc(unsigned char *crc, unsigned char val)
{
 *crc ^= val;
}