void basename_discriminant(char *filename,long *h,long *len)

{
  char *pcVar1;
  char *stt;
  long *len_local;
  long *h_local;
  char *filename_local;
  
  pcVar1 = strrchr(filename,0x2f);
  stt = filename;
  if (pcVar1 != (char *)0x0) {
    stt = pcVar1 + 1;
  }
  *len = 0;
  *h = 0;
  while (*stt != '\0') {
    *h = *h * 0x21;
    *h = (long)*stt + *h;
    *len = *len + 1;
    stt = stt + 1;
  }
  return;
}