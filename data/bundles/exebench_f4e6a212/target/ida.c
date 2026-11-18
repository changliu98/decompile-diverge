void __cdecl mix_16h_to_32_s2(int *dest_buf, short *mp3_buf, int count)
{
  int *v4; // rax
  int counta; // [rsp+0h] [rbp-14h]

  counta = count >> 1;
  while ( counta-- )
  {
    *dest_buf += *mp3_buf >> 1;
    v4 = dest_buf + 1;
    dest_buf += 2;
    *v4 += mp3_buf[1] >> 1;
    mp3_buf += 8;
  }
}