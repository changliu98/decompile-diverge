void encrypt(char *c) {
 int i = 0;
 while(c[i] != '\0') {
  c[i++] += 5;
 }
}