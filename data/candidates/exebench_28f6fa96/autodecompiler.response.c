int arikkei_ucs2_strncpy(short unsigned *src, short unsigned *des, unsigned int length)
{
 register unsigned char *s = (unsigned char *)src;
 register unsigned char *d = (unsigned char *)des;
 unsigned int i = 0;

 if (length < 1) {
  while (1) {
   if (*(short unsigned *)d != 0) {
    *(short unsigned *)des = *(short unsigned *)d;
    d += 2;
    i++;
   } else {
    *(short unsigned *)des = 0;
    break;
   }
  }
 } else {
  while (1) {
   if ((*(short unsigned *)d != 0) && (i < length)) {
    *(short unsigned *)des = *(short unsigned *)d;
    d += 2;
    i++;
   } else {
    if (i < length)
     *(short unsigned *)des = 0;
    break;
   }
  }
 }
 return i;
}