char *get_dir(char *file)
{
  char *dir;
  unsigned long len = dir_len(file);
  if ((dir = (char *)malloc(len + (len == 0) + 1)) == ((void *)0))
    return ((void *)0);
  memcpy(dir, file, len);
  if (len == 0) {
    len = 1;
    dir[0] = '.';
  }
  dir[len] = '\0';
  return dir;
}