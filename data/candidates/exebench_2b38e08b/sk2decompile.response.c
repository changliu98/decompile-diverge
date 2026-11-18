void copy_string(char *to, char *from, int n) {
  int i;
  i = 0;
  while (i < n && (to[i] = from[i]) != '\0') i++;
}