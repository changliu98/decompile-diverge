void scsi_sanitize_inquiry_string(uchar *s,int len)

{
  bool bVar1;
  int terminated;
  int len_local;
  uchar *s_local;
  
  bVar1 = false;
  s_local = s;
  for (len_local = len; 0 < len_local; len_local = len_local + -1) {
    if (*s_local == '\0') {
      bVar1 = true;
    }
    if (((bVar1) || (*s_local < 0x20)) || (0x7e < *s_local)) {
      *s_local = ' ';
    }
    s_local = s_local + 1;
  }
  return;
}