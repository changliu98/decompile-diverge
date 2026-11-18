void bitfile_read(struct bitfile *bf, int bits)
{
  unsigned int tmp;
  int words = bits / 32;
  bf->bytes_left = bf->buffer_size - words * 4;
  if (bf->bytes_left >= 4)
  {
    tmp = get_le_int(&bf->start[words]);
    bf->bytes_left -= 4;
  }
  else
  {
    tmp = get_le_int(&bf->start[words], bf->bytes_left);
    bf->bytes_left = 0;
  }
  bf->bufa = tmp;
  if (bf->bytes_left >= 4)
  {
    tmp = get_le_int(&bf->start[words + 1]);
    bf->bytes_left -= 4;
  }
  else
  {
    tmp = get_le_int(&bf->start[words + 1], bf->bytes_left);
    bf->bytes_left = 0;
  }
  bf->bufb = tmp;
  bf->bits_left = 32 - (bits % 32);
  bf->tail = &bf->start[words + 2];
  bf->error = 0;
}