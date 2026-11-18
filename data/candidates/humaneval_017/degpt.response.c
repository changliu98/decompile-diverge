int * func0(char *music_string,int *count)

{
  int iVar1;
  size_t sVar2;
  char *__dest;
  size_t sVar3;
  int local_54;
  int local_50;
  int local_4c;
  size_t len;
  int i;
  char *temp_music_string;
  int music_string_length;
  char current [3];
  int capacity;
  int size;
  int *out;
  int *count_local;
  char *music_string_local;
  
  out = (int *)0x0;
  size = 0;
  capacity = 0;
  memset(current,0,3);
  sVar2 = strlen(music_string);
  __dest = malloc((long)((int)sVar2 + 2));
  strcpy(__dest,music_string);
  strcat(__dest," ");
  for (i = 0; i < (int)sVar2 + 1; i = i + 1) {
    if (__dest[i] == ' ') {
      iVar1 = strcmp(current,"o");
      if (iVar1 == 0) {
        if (size == capacity) {
          if (capacity < 1) {
            local_4c = 4;
          }
          else {
            local_4c = capacity << 1;
          }
          capacity = local_4c;
          out = realloc(out,(long)local_4c << 2);
        }
        out[size] = 4;
        size = size + 1;
      }
      iVar1 = strcmp(current,"o|");
      if (iVar1 == 0) {
        if (size == capacity) {
          if (capacity < 1) {
            local_50 = 4;
          }
          else {
            local_50 = capacity << 1;
          }
          capacity = local_50;
          out = realloc(out,(long)local_50 << 2);
        }
        out[size] = 2;
        size = size + 1;
      }
      iVar1 = strcmp(current,".|");
      if (iVar1 == 0) {
        if (size == capacity) {
          if (capacity < 1) {
            local_54 = 4;
          }
          else {
            local_54 = capacity << 1;
          }
          capacity = local_54;
          out = realloc(out,(long)local_54 << 2);
        }
        out[size] = 1;
        size = size + 1;
      }
      strcpy(current,"");
    }
    else {
      sVar3 = strlen(current);
      if (sVar3 < 2) {
        current[sVar3] = __dest[i];
        current[sVar3 + 1] = '\0';
      }
    }
  }
  free(__dest);
  *count = size;
  return out;
}