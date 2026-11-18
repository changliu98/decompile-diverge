/* WARNING: Removing unreachable block (ram,0x0010129b) */

char * base_name(char *name)

{
  size_t sVar1;
  char *__dest;
  char *p;
  int dotslash_len;
  idx_t length;
  char *base;
  char *name_local;
  
  base = last_component(name);
  if (*base == '\0') {
    length = base_len(name);
    base = name;
  }
  else {
    sVar1 = base_len(base);
    length = (long)(int)(uint)(base[sVar1] == '/') + sVar1;
  }
  __dest = ximalloc(length + 1);
  memcpy(__dest,base,length);
  __dest[length] = '\0';
  return __dest;
}