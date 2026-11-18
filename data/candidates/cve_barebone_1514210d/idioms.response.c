int parse_device(void *arg, struct archive *a, char *val)
{
  char *end;
  char *end2;
  int i;
  int *dev = arg;
  char *fmt = val;
  char *err = ((void *)0);
  char *packname = ((void *)0);
  pack_t *pack;
  unsigned long long numbers[3];
  end = getend(val, ',');
  if (end == ((void *)0))
    return *dev = getll(&fmt);
  *end++ = '\0';
  pack = getpack(val);
  if (pack == ((void *)0)) {
    arch_err(a, 22, "Unknown format `%s'", val);
    return -20;
  }
  for (i = 0; (end2 = getend(&end, ",")); i++) {
    if (*end2 == '\0') {
      arch_err(a, 22, "Missing number");
      return -20;
    }
    numbers[i++] = getll(&end2);
    if (i > 3) {
      arch_err(a, 22, "Too many arguments");
      return -20;
    }
  }
  if (i < 2) {
    arch_err(a, 22, "Not enough arguments");
    return -20;
  }
  if ((err = pack(i, numbers, &packname)) != ((void *)0)) {
    arch_err(a, 22, "%s", err);
    return -20;
  }
  return *dev = packname;
}