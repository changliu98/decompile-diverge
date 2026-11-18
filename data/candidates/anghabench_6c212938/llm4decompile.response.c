void copy_le16(unsigned char *out, uint16_t in)
{
    out[0] = in & 0xff;
    out[1] = (in >> 8) & 0xff;
}