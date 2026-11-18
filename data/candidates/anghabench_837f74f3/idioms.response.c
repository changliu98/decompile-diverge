void set_bit(unsigned char *data, unsigned long pos)
{
  data[pos / 8] |= 1 << (7 - (pos % 8));
}