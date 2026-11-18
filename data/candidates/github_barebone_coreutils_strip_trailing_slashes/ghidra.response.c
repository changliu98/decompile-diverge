_Bool strip_trailing_slashes(char *file)

{
  char cVar1;
  size_t sVar2;
  _Bool had_slash;
  char *base_lim;
  char *base;
  char *file_local;
  
  base = last_component(file);
  if (*base == '\0') {
    base = file;
  }
  sVar2 = base_len(base);
  cVar1 = base[sVar2];
  base[sVar2] = '\0';
  return cVar1 != '\0';
}