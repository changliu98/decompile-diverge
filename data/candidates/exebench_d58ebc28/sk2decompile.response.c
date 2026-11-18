void dummyfunc(char *str) {
  char *ptr = str;
  int i = 0;
  char str2[] = "Goodbye";
  while (ptr[i] != '\0') {
    ptr[i] = str2[i];
    i++;
  }
}