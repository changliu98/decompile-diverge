void add_crc(char *buf, char c)
{
 buf[0] ^= c;
}