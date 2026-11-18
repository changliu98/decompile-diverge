void set_mask(int *mask,int size,int offset,int length)

{
  int i;
  int length_local;
  int offset_local;
  int size_local;
  int *mask_local;
  
  if (0 < offset) {
    *mask = -offset;
  }
  i = (int)(0 < offset);
  mask[i] = length;
  mask[i + 1] = -((size - offset) - length);
  mask[i + 2] = 0;
  return;
}