void byte2bits(char c, char *bin) {
 int i;
 for(i = 7; i >= 0; i--) {
  *bin++ = ((c >> i) & 1) + '0';
 }
 *bin = '\0';
}