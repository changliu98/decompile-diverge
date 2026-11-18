njs_int_t njs_module_path(njs_vm_t *vm,njs_str_t *dir,njs_module_info_t *info)

{
  int iVar1;
  char *pcVar2;
  size_t sVar3;
  bool bVar4;
  char src [4097];
  njs_bool_t trail;
  size_t length;
  char *p;
  njs_module_info_t *info_local;
  njs_str_t *dir_local;
  njs_vm_t *vm_local;
  njs_int_t local_10;
  
  bVar4 = false;
  length = (info->name).length;
  if (dir != (njs_str_t *)0x0) {
    length = dir->length;
    if (length == 0) {
      return -3;
    }
    bVar4 = dir->start[dir->length - 1] != '/';
    if (bVar4) {
      length = length + 1;
    }
  }
  if (length < 0x1001) {
    p = src;
    if (dir != (njs_str_t *)0x0) {
      memcpy(src,dir->start,dir->length);
      pcVar2 = src + dir->length;
      p = pcVar2;
      if (bVar4) {
        p = src + dir->length + 1;
        *pcVar2 = '/';
      }
    }
    memcpy(p,(info->name).start,(info->name).length);
    p[(info->name).length] = '\0';
    pcVar2 = realpath(src,info->path);
    if (pcVar2 == (char *)0x0) {
      local_10 = -3;
    }
    else {
      iVar1 = open(info->path,0);
      info->fd = iVar1;
      if (info->fd < 0) {
        local_10 = -3;
      }
      else {
        (info->file).start = (u_char *)info->path;
        sVar3 = strlen((char *)(info->file).start);
        (info->file).length = sVar3;
        local_10 = 0;
      }
    }
  }
  else {
    local_10 = -1;
  }
  return local_10;
}