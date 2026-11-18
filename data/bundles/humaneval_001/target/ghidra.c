char ** func0(char *paren_string,int *group_count)

{
  size_t sVar1;
  char *__s;
  char *pcVar2;
  int iVar3;
  char chr;
  int i;
  int buffer_index;
  char *buffer;
  char **groups;
  int capacity;
  int level;
  int length;
  int *group_count_local;
  char *paren_string_local;
  
  sVar1 = strlen(paren_string);
  level = 0;
  capacity = 10;
  groups = malloc(0x50);
  __s = malloc((long)((int)sVar1 + 1));
  buffer_index = 0;
  *group_count = 0;
  for (i = 0; i < (int)sVar1; i = i + 1) {
    if (paren_string[i] == '(') {
      level = level + 1;
      __s[buffer_index] = '(';
      buffer_index = buffer_index + 1;
    }
    else if (paren_string[i] == ')') {
      level = level + -1;
      iVar3 = buffer_index + 1;
      __s[buffer_index] = ')';
      buffer_index = iVar3;
      if (level == 0) {
        __s[iVar3] = '\0';
        pcVar2 = strdup(__s);
        groups[*group_count] = pcVar2;
        *group_count = *group_count + 1;
        if (capacity <= *group_count) {
          capacity = capacity << 1;
          groups = realloc(groups,(long)capacity << 3);
        }
        buffer_index = 0;
      }
    }
  }
  free(__s);
  return groups;
}