int file_perms_get(char *name, int *group, int *mode)
{
  struct stat stbuf;
  if (*group != 0) *group = 0;
  if (*mode != 0) *mode = 0;

  if (_stat(name, &stbuf) < 0)
    return;
  if (group != NULL) *group = stbuf.st_gid;
  if (mode != NULL) *mode = (stbuf.st_mode & 07777);
}