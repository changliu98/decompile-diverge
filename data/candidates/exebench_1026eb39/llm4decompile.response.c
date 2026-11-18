void ut32_unpack(const char *buf, uint32_t *i)
{
    *i = (unsigned char)buf[0] + (((unsigned char)buf[1])<<8) + (((unsigned char)buf[2])<<16) + (((unsigned char)buf[3])<<24);
}