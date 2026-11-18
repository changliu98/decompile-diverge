static unsigned long base_len(char *name)
{
  unsigned long len = strlen(name);
  while (1) {
    _Bool is_dir = 0;
    if (len > 1)
      is_dir = name[len - 1] == '/';
    if (!is_dir)
      break;
    --len;
  }
  return len;
}