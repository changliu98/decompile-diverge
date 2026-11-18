char *
mdir_name (char const *file)
{
  size_t length = dir_len (file);
  bool append_dot = (length == 0
                     || (FILE_SYSTEM_DRIVE_PREFIX_CAN_BE_RELATIVE
                         && length == FILE_SYSTEM_PREFIX_LEN (file)
                         && file[2] != '\0' && ! ISSLASH (file[2])));
  char *dir = malloc (length + append_dot + 1);
  if (!dir)
    return NULL;
  memcpy (dir, file, length);
  if (append_dot)
    dir[length++] = '.';
  dir[length] = '\0';
  return dir;
}