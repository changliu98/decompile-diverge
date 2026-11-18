char * func0(char *str,char ch)

{
  int iVar1;
  size_t sVar2;
  char *new_str;
  int i_3;
  int i_2;
  int i_1;
  int new_index;
  char *new_str_1;
  int i;
  int last;
  int first;
  int len;
  char ch_local;
  char *str_local;
  char *local_10;
  
  sVar2 = strlen(str);
  iVar1 = (int)sVar2;
  first = -1;
  last = -1;
  for (i = 0; i < iVar1; i = i + 1) {
    if (str[i] == ch) {
      if (first == -1) {
        first = i;
      }
      last = i;
    }
  }
  if (((first == -1) || (last == -1)) || (first == last)) {
    local_10 = malloc((long)(iVar1 + 1));
    strcpy(local_10,str);
  }
  else {
    local_10 = malloc((long)(iVar1 + -1));
    new_index = 0;
    for (i_1 = 0; i_2 = first, i_1 < first; i_1 = i_1 + 1) {
      local_10[new_index] = str[i_1];
      new_index = new_index + 1;
    }
    while (i_2 = i_2 + 1, i_3 = last, i_2 < last) {
      local_10[new_index] = str[i_2];
      new_index = new_index + 1;
    }
    while (i_3 = i_3 + 1, i_3 < iVar1) {
      local_10[new_index] = str[i_3];
      new_index = new_index + 1;
    }
    local_10[new_index] = '\0';
  }
  return local_10;
}