int cpy(char *a,char *b)

{
  int i;
  char *b_local;
  char *a_local;
  
  for (i = 0; b[i] != '\0' && i < 100; i = i + 1) {
    a[i] = b[i];
  }
  a[i] = '\0';
  return 0;
}