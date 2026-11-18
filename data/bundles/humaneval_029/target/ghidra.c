int func0(char **strings,int count,char *prefix,char ***out)

{
  int iVar1;
  size_t sVar2;
  char **ppcVar3;
  int i;
  int out_count;
  int prefix_length;
  char ***out_local;
  char *prefix_local;
  int count_local;
  char **strings_local;
  
  sVar2 = strlen(prefix);
  ppcVar3 = malloc((long)count << 3);
  *out = ppcVar3;
  out_count = 0;
  for (i = 0; i < count; i = i + 1) {
    iVar1 = strncmp(strings[i],prefix,(long)(int)sVar2);
    if (iVar1 == 0) {
      (*out)[out_count] = strings[i];
      out_count = out_count + 1;
    }
  }
  return out_count;
}