char itochar(int i, char *c) {
 char tmp[32];
 unsigned char j = 0;
 do {
  tmp[j++] = (i % 10) + '0';
 } while (i /= 10);
 j--;
 for (unsigned char k = 0; k < j; k++) {
  c[k] = tmp[j-k-1];
 }
 return j;
}