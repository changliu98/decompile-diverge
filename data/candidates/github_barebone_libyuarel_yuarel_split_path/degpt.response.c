int yuarel_split_path(char *path,char **parts,int max_parts)

{
  char *pcVar1;
  int iVar2;
  int i;
  int max_parts_local;
  char **parts_local;
  char *path_local;
  int local_c;
  
  i = 0;
  if ((path == (char *)0x0) || (path_local = path, *path == '\0')) {
    local_c = -1;
  }
  else {
    do {
      for (; *path_local == '/'; path_local = path_local + 1) {
      }
      if (*path_local == '\0') break;
      iVar2 = i + 1;
      parts[i] = path_local;
      pcVar1 = strchr(path_local,0x2f);
      i = iVar2;
      if (pcVar1 == (char *)0x0) break;
      path_local = pcVar1 + 1;
      *pcVar1 = '\0';
    } while (iVar2 < max_parts);
    local_c = i;
  }
  return local_c;
}