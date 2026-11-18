char * func0(char *string)

{
  bool bVar1;
  int iVar2;
  char *__s;
  size_t sVar3;
  int i_2;
  char *result;
  int i_1;
  int total_length;
  int i;
  int found;
  char *token;
  int unique_count;
  char *unique [100];
  char *str;
  char *string_local;
  char *local_10;
  
  __s = strdup(string);
  if (__s == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    unique_count = 0;
    token = strtok(__s," ");
    while (token != (char *)0x0) {
      bVar1 = false;
      for (i = 0; i < unique_count; i = i + 1) {
        iVar2 = strcmp(token,unique[i]);
        if (iVar2 == 0) {
          bVar1 = true;
          break;
        }
      }
      if (!bVar1) {
        unique[unique_count] = token;
        unique_count = unique_count + 1;
      }
      token = strtok((char *)0x0," ");
    }
    total_length = 0;
    for (i_1 = 0; i_1 < unique_count; i_1 = i_1 + 1) {
      sVar3 = strlen(unique[i_1]);
      total_length = total_length + (int)sVar3 + 1;
    }
    local_10 = malloc((long)total_length);
    if (local_10 == (char *)0x0) {
      free(__s);
      local_10 = (char *)0x0;
    }
    else {
      *local_10 = '\0';
      for (i_2 = 0; i_2 < unique_count; i_2 = i_2 + 1) {
        strcat(local_10,unique[i_2]);
        if (i_2 < unique_count + -1) {
          strcat(local_10," ");
        }
      }
      free(__s);
    }
  }
  return local_10;
}