void get_file_stat(char *path, int *p_group, int *p_mode)
{
  struct stat st;
  if (*p_group != 0)
    *p_group = 0;
  if (*p_mode != 0)
    *p_mode = 0;
  if (stat(path, &st) < 0)
    return;
  if (p_group != ((void *)0))
    *p_group = st.st_gid;
  if (p_mode != ((void *)0))
    *p_mode = st.st_mode & 0777;
}