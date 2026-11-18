char ** func0(char **strings,int size,char *substring,int *out_size)

{
  char *pcVar1;
  int i;
  int count;
  char **out;
  int *out_size_local;
  char *substring_local;
  int size_local;
  char **strings_local;
  
  out = (char **)0x0;
  count = 0;
  for (i = 0; i < size; i = i + 1) {
    pcVar1 = strstr(strings[i],substring);
    if (pcVar1 != (char *)0x0) {
      out = realloc(out,(long)(count + 1) << 3);
      out[count] = strings[i];
      count = count + 1;
    }
  }
  *out_size = count;
  return out;
}