
void mix_16h_to_32_s2(int *dest_buf, short *mp3_buf, int count)
{
 count >>= 1;
 while (count--)
 {
  *dest_buf++ += *mp3_buf++ >> 1;
  *dest_buf++ += *mp3_buf++ >> 1;
  mp3_buf += 3*2;
 }
}
