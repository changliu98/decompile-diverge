char ** func0(char *s,int *count)

{
  size_t sVar1;
  char *__s;
  char *pcVar2;
  int iVar3;
  int i;
  int current_length;
  int word_count;
  char *current;
  char **out;
  int capacity;
  int *count_local;
  char *s_local;
  
  capacity = 10;
  out = malloc(0x50);
  sVar1 = strlen(s);
  __s = malloc(sVar1 + 1);
  word_count = 0;
  current_length = 0;
  for (i = 0; s[i] != '\0'; i = i + 1) {
    if ((s[i] == ' ') || (s[i] == ',')) {
      if (0 < current_length) {
        __s[current_length] = '\0';
        pcVar2 = strdup(__s);
        iVar3 = word_count + 1;
        out[word_count] = pcVar2;
        current_length = 0;
        word_count = iVar3;
        if (capacity <= iVar3) {
          capacity = capacity << 1;
          out = realloc(out,(long)capacity << 3);
        }
      }
    }
    else {
      __s[current_length] = s[i];
      current_length = current_length + 1;
    }
  }
  if (0 < current_length) {
    __s[current_length] = '\0';
    pcVar2 = strdup(__s);
    out[word_count] = pcVar2;
    word_count = word_count + 1;
  }
  free(__s);
  *count = word_count;
  return out;
}