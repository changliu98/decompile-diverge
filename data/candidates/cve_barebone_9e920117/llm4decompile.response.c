njs_int_t
njs_module_path(njs_vm_t *vm, njs_str_t *dir, njs_module_info_t *info)
{
  char path[4096];
  size_t len;
  njs_bool_t trail;

  len = (dir != NULL) ? dir->length : (info->name).length;
  trail = dir != NULL && dir->start[dir->length - 1] != '/';
  if (trail)
    len++;

  if (len > sizeof(path))
    return -1;

  if (dir != NULL) {
    memcpy(path, dir->start, dir->length);
    if (trail)
      path[dir->length] = '/';
  }

  memcpy(path + (dir != NULL ? dir->length : 0),
         (info->name).start, (info->name).length);
  path[len] = '\0';

  if (realpath(path, info->path) == NULL)
    return -3;

  info->fd = open(info->path, 0);
  if (info->fd < 0)
    return -3;

  (info->file).start = info->path;
  (info->file).length = strlen((info->file).start);

  return 0;
}