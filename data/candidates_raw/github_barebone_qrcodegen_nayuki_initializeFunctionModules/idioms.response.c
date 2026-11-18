void make_frame(int version, unsigned char *frame)
{
  int i; int j;
  int size;
  int numAlign;
  int alignPos[7];
  size = 4 * version + 17;
  clear_frame(frame, 0, (size * size + 7) / 8 + 1);
  frame[0] = size;
  make_box(6, 0, 1, size, frame);
  make_box(0, 6, size, 1, frame);
  make_box(0, 0, 9, 9, frame);
  make_box(size - 8, 0, 8, 9, frame);
  make_box(0, size - 8, 9, 8, frame);
  numAlign = get_alignment(version, alignPos);
  for (i = 0; i < numAlign; i++)
    for (j = 0; j < numAlign; j++)
      if (i == 0 && j == 0)
        continue;
      else if (i == numAlign - 1 && j == numAlign - 1)
        continue;
      else
        make_box(alignPos[i] - 2, alignPos[j] - 2, 5, 5, frame);
  if (version >= 7) {
    make_box(size - 11, 0, 3, 6, frame);
    make_box(0, size - 11, 6, 3, frame);
  }
}