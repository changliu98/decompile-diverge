void mix_16h_to_32_s2(int *dest_buf,short *mp3_buf,int count)

{
  int *piVar1;
  int count_local;
  short *mp3_buf_local;
  int *dest_buf_local;
  
  count_local = count >> 1;
  mp3_buf_local = mp3_buf;
  dest_buf_local = dest_buf;
  while (count_local != 0) {
    piVar1 = dest_buf_local + 1;
    *dest_buf_local = ((int)*mp3_buf_local >> 1) + *dest_buf_local;
    dest_buf_local = dest_buf_local + 2;
    *piVar1 = ((int)mp3_buf_local[1] >> 1) + *piVar1;
    mp3_buf_local = mp3_buf_local + 8;
    count_local = count_local + -1;
  }
  return;
}