char *byte_to_binary(char x, char *str) {
 int z;
 for (z = 0; z < 9; z++) {
  str[z] = ((x & (1 << (7-z))) ? '1' : '0');
 }
 str[8] = '\0';
 return str;
}