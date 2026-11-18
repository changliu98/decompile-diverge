void file_perms_get(uchar *path,int *p_group,int *p_mode)

{
  int iVar1;
  stat stb;
  int *p_mode_local;
  int *p_group_local;
  uchar *path_local;
  
  if (*p_group != 0) {
    *p_group = 0;
  }
  if (*p_mode != 0) {
    *p_mode = 0;
  }
  iVar1 = stat((char *)path,(stat *)&stb);
  if (-1 < iVar1) {
    if (p_group != (int *)0x0) {
      *p_group = stb.st_gid;
    }
    if (p_mode != (int *)0x0) {
      *p_mode = stb.st_mode & 0xfff;
    }
  }
  return;
}