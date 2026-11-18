void arx_bwd(unsigned char *block)
{
 block[2] = (((block[2]) << 4) & 0xF0) | (((block[2]) >> 4) & 0x0F);
 block[1] ^= block[2];
 block[3] ^= block[0];
 block[1] = (((block[1]) << 5) & 0xE0) | (((block[1]) >> 3) & 0x1F);
 block[3] = (((block[3]) << 1) & 0xFE) | (((block[3]) >> 7) & 0x01);
 block[0] -= block[3];
 block[2] -= block[1];
 block[0] = (((block[0]) << 4) & 0xF0) | (((block[0]) >> 4) & 0x0F);
 block[1] ^= block[0];
 block[3] ^= block[2];
 block[1] = (((block[1]) << 6) & 0xC0) | (((block[1]) >> 2) & 0x3F);
 block[3] = (((block[3]) << 3) & 0xF8) | (((block[3]) >> 5) & 0x07);
 block[0] -= block[1];
 block[2] -= block[3];
}