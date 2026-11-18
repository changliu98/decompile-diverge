char * mfile_name_concat(char *dir,char *base,char **base_in_result)

{
  char *pcVar1;
  size_t sVar2;
  size_t __n;
  char *p;
  char *p_concat;
  char sep;
  size_t baselen;
  size_t dirlen;
  size_t dirbaselen;
  char *dirbase;
  char **base_in_result_local;
  char *base_local;
  char *dir_local;
  char *local_10;
  
  pcVar1 = last_component(dir);
  sVar2 = base_len(pcVar1);
  pcVar1 = pcVar1 + (sVar2 - (long)dir);
  __n = strlen(base);
  sep = '\0';
  if (sVar2 == 0) {
    if (*base == '/') {
      sep = '.';
    }
  }
  else if ((dir[(long)(pcVar1 + -1)] != '/') && (*base != '/')) {
    sep = '/';
  }
  local_10 = malloc((size_t)(pcVar1 + __n + (long)(int)(uint)(sep != '\0') + 1));
  if (local_10 == (char *)0x0) {
    local_10 = (char *)0x0;
  }
  else {
    memcpy(local_10,dir,(size_t)pcVar1);
    local_10[(long)pcVar1] = sep;
    pcVar1 = local_10 + (long)pcVar1 + (int)(uint)(sep != '\0');
    if (base_in_result != (char **)0x0) {
      *base_in_result = pcVar1;
    }
    memcpy(pcVar1,base,__n);
    pcVar1[__n] = '\0';
  }
  return local_10;
}