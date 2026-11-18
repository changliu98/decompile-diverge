char *mdir_name(const char *file)
{
  size_t length = dir_len(file);
  char *dir = malloc(length + (length == 0) + 1);
  if (dir == NULL)
    return NULL;
  memcpy(dir, file, length);
  if (length == 0)
    dir[length++] = '.';
  dir[length] = '\0';
  return dir;
}