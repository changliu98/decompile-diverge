int file_perms_get(const char *path, int *p_group, int *p_mode)
{
 int result;
 struct stat statbuf;

 if(*p_group)
  *p_group = 0;
 if(*p_mode)
  *p_mode = 0;

 result = stat(path, &statbuf);
 if(result < 0)
  return result;

 if(p_group)
  *p_group = statbuf.st_gid;
 if(p_mode)
  *p_mode = statbuf.st_mode & 07777;

 return result;
}