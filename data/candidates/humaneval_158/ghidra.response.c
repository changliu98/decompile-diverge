char * func0(char **words,int count)

{
  int iVar1;
  char *pcVar2;
  size_t sVar3;
  int len;
  int j;
  int unique_count;
  char unique [256];
  int i;
  int maxu;
  char *max;
  int count_local;
  char **words_local;
  
  max = "";
  maxu = 0;
  i = 0;
  do {
    if (count <= i) {
      return max;
    }
    memset(unique,0,0x100);
    unique_count = 0;
    for (j = 0; words[i][j] != '\0'; j = j + 1) {
      pcVar2 = strchr(unique,(int)words[i][j]);
      if (pcVar2 == (char *)0x0) {
        sVar3 = strlen(unique);
        unique[(int)sVar3] = words[i][j];
        unique[(int)sVar3 + 1] = '\0';
        unique_count = unique_count + 1;
      }
    }
    if (maxu < unique_count) {
LAB_00101388:
      max = words[i];
      maxu = unique_count;
    }
    else if (unique_count == maxu) {
      iVar1 = strcmp(words[i],max);
      if (iVar1 < 0) goto LAB_00101388;
    }
    i = i + 1;
  } while( true );
}