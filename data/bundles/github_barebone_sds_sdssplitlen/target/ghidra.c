sds * sdssplitlen(char *s,ssize_t len,char *sep,int seplen,int *count)

{
  int iVar1;
  sds *ppcVar2;
  sds pcVar3;
  int i;
  sds *newtokens;
  sds *tokens;
  long j;
  long start;
  int slots;
  int elements;
  int *count_local;
  int seplen_local;
  char *sep_local;
  ssize_t len_local;
  char *s_local;
  sds *local_10;
  
  elements = 0;
  slots = 5;
  start = 0;
  if ((seplen < 1) || (len < 1)) {
    *count = 0;
    local_10 = (sds *)0x0;
  }
  else {
    tokens = malloc(0x28);
    if (tokens == (sds *)0x0) {
      local_10 = (sds *)0x0;
    }
    else {
      for (j = 0; j < len - (seplen + -1); j = j + 1) {
        ppcVar2 = tokens;
        if (slots < elements + 2) {
          slots = slots << 1;
          ppcVar2 = realloc(tokens,(long)slots << 3);
          if (ppcVar2 == (sds *)0x0) goto LAB_0010367d;
        }
        tokens = ppcVar2;
        if (((seplen == 1) && (s[j] == *sep)) ||
           (iVar1 = memcmp(s + j,sep,(long)seplen), iVar1 == 0)) {
          pcVar3 = sdsnewlen(s + start,j - start);
          tokens[elements] = pcVar3;
          if (tokens[elements] == (sds)0x0) goto LAB_0010367d;
          elements = elements + 1;
          start = j + seplen;
          j = j + seplen + -1;
        }
      }
      pcVar3 = sdsnewlen(s + start,len - start);
      tokens[elements] = pcVar3;
      if (tokens[elements] == (sds)0x0) {
LAB_0010367d:
        for (i = 0; i < elements; i = i + 1) {
          sdsfree(tokens[i]);
        }
        free(tokens);
        *count = 0;
        local_10 = (sds *)0x0;
      }
      else {
        *count = elements + 1;
        local_10 = tokens;
      }
    }
  }
  return local_10;
}