void __cdecl mix_16h_to_32_s2(int *dest_buf, short *mp3_buf, int count)
{
  int counta = count >> 1;

  while (counta--)
  {
    dest_buf[0] += mp3_buf[0] >> 1;
    dest_buf[1] += mp3_buf[1] >> 1;

    dest_buf += 2;
    mp3_buf += 8;
  }
}