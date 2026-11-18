njs_int_t __cdecl njs_module_path(njs_vm_t *vm, const njs_str_t *dir, njs_module_info_t *info)
{
  char path_buf[4097]; // Stack buffer for constructing the full path
  njs_bool_t need_slash;
  size_t length;
  char *p;
  char *ret;

  // Unused in logic, but preserved for semantic completeness
  (void)vm;

  need_slash = 0;
  length = info->name.length;

  if (dir) {
    length = dir->length;
    if (length == 0) {
      return NJS_ERROR; // -3
    }

    // Check if the directory path lacks a trailing slash ('/' == 47)
    need_slash = (dir->start[dir->length - 1] != '/');

    // Account for the extra slash character in the total length
    if (need_slash) {
      length++;
    }
  }

  // Check if the combined path exceeds the buffer limit (0x1000 = 4096)
  if (length > 0x1000) {
    return NJS_DECLINED; // -1
  }

  p = path_buf;

  // Append the directory path if provided
  if (dir) {
    memcpy(p, dir->start, dir->length);
    p += dir->length;

    // Append the missing slash if necessary
    if (need_slash) {
      *p++ = '/';
    }
  }

  // Append the module name
  memcpy(p, info->name.start, info->name.length);
  p += info->name.length;

  // Null-terminate the constructed path
  *p = '\0';

  // Resolve the absolute path and store it in info->path
  ret = realpath(path_buf, info->path);
  if (!ret) {
    return NJS_ERROR; // -3
  }

  // Open the resolved file path (O_RDONLY == 0)
  info->fd = open(info->path, O_RDONLY);
  if (info->fd < 0) {
    return NJS_ERROR; // -3
  }

  // Set file info and calculate its string length
  info->file.start = (u_char *)info->path;
  info->file.length = strlen((const char *)info->file.start);

  return NJS_OK; // 0
}