char * last_component(char *name)

{
  bool bVar1;
  char *p;
  _Bool last_was_slash;
  char *base;
  char *name_local;
  
  for (base = name; *base == '/'; base = base + 1) {
  }
  bVar1 = false;
  for (p = base; *p != '\0'; p = p + 1) {
    if (*p == '/') {
      bVar1 = true;
    }
    else if (bVar1) {
      base = p;
      bVar1 = false;
    }
  }
  return base;
}