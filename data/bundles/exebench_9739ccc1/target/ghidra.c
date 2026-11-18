void set_stimulus(uchar *dst,char *p)

{
  char *p_local;
  uchar *dst_local;
  
  for (p_local = p; *p_local != '\0'; p_local = p_local + 1) {
    if (('/' < *p_local) && (*p_local < '8')) {
      *dst = *dst & ((byte)(1 << (*p_local - 0x30U & 0x1f)) ^ 0xff);
    }
  }
  return;
}