void get_mask(int *mask, int size, int offset, int length)
{
  int i = 0;
  if (offset > 0) {
    mask[i++] = -offset;
  }
  mask[i++] = length;
  mask[i++] = length - (size - offset);
  mask[i++] = 0;
}