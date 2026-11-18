char *base_name(char *path)
{
  char *base;
  unsigned long len;
  char *name;
  name = last_component(path);
  if (*name == '\0') {
    base = path;
    len = base_len(path);
  } else {
    base = name;
    len = base_len(name) + (base[base_len(name)] == '/');
  }
  name = ximalloc(len + 1);
  memcpy(name, base, len);
  name[len] = '\0';
  return name;
}