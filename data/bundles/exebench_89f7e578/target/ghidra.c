void put_num(unsigned_short *dst,uint num,uchar len)

{
  uchar len_local;
  uint num_local;
  unsigned_short *dst_local;
  
  dst_local = dst;
  if (4 < len) {
    dst_local = dst + 1;
    *dst = (short)(((ulong)num / 10000) % 10) + 0x10U | 0x2100;
  }
  if (3 < len) {
    *dst_local = (short)(((ulong)num / 1000) % 10) + 0x10U | 0x2100;
    dst_local = dst_local + 1;
  }
  if (2 < len) {
    *dst_local = (short)(((ulong)num / 100) % 10) + 0x10U | 0x2100;
    dst_local = dst_local + 1;
  }
  if (1 < len) {
    *dst_local = (short)(((ulong)num / 10) % 10) + 0x10U | 0x2100;
    dst_local = dst_local + 1;
  }
  if (len != '\0') {
    *dst_local = (short)(num % 10) + 0x10U | 0x2100;
  }
  return;
}