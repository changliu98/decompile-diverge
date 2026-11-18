int jpeg_size(unsigned char *data, int data_size, int *width, int *height)
{
  int i; int j;
  unsigned short block_length;
  if (data_size < 4 ||
      data[0] != 0xff ||
      data[1] != 0xd8 ||
      data[2] != 0xff ||
      data[3] != 0xe0)
    return -1;
  i = 4;
  if (data_size < i + 5 ||
      data[i + 0] != 'J' ||
      data[i + 1] != 'F' ||
      data[i + 2] != 'I' ||
      data[i + 3] != 'F' ||
      data[i + 4] != 0)
    return -1;
  block_length = data[i + 2] + (data[i + 1] << 8);
  for (i += 2; i < data_size;) {
    j = i + block_length;
    if (j + 1 >= data_size)
      return -1;
    if (data[j] != 0xff)
      return -1;
    if (data[j + 1] == 0xc0) {
      *height = data[j + 5] + (data[j + 4] << 8);
      *width = data[j + 7] + (data[j + 6] << 8);
      return 0;
    }
    i = j + 2;
    block_length = data[i + 1] + (data[i + 0] << 8);
  }
  return -1;
}