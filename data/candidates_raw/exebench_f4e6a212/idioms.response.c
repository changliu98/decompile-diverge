void deinterleave_mp3(int *dest, short *mp3, int count)
{
  int i = count / 2;
  while (i--) {
    *dest++ += *mp3++ >> 1;
    *dest++ += *(mp3 + 1) >> 1;
    mp3 += 6;
  }
}