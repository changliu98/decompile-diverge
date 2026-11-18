char * upcase(char *orig)

{
  int i;
  char *orig_local;
  
  for (i = 0; orig[i] != '\0'; i = i + 1) {
    if (('`' < orig[i]) && (orig[i] < '{')) {
      orig[i] = orig[i] + -0x20;
    }
  }
  return orig;
}