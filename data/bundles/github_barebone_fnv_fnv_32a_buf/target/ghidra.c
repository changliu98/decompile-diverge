Fnv32_t fnv_32a_buf(void *buf,size_t len,Fnv32_t hval)

{
  uchar *be;
  uchar *bp;
  Fnv32_t hval_local;
  size_t len_local;
  void *buf_local;
  
  hval_local = hval;
  for (bp = buf; bp < (uchar *)((long)buf + len); bp = bp + 1) {
    hval_local = (*bp ^ hval_local) * 0x1000193;
  }
  return hval_local;
}