njs_int_t njs_module_path(njs_vm_t *vm, njs_str_t *base, njs_module_t *module) {
  char path[4096 + 1];
  char *p;
  njs_uint_t slash;
  njs_uint_t len;
  njs_uint_t n;
  slash = 0;
  len = module->path.length;
  if (base != NULL) {
    len = base->length;
    if (len == 0) {
      return -3;
    }
    slash = base->start[len - 1] != '/';
    if (slash) {
      len++;
    }
  }
  if (len > 4096) {
    return -1;
  }
  p = path;
  if (base != NULL) {
    memcpy(p, base->start, base->length);
    p += base->length;
    if (slash) {
      *p++ = '/';
    }
  }
  n = p - path;
  memcpy(p, module->path.start, module->path.length);
  p += module->path.length;
  *p = '\0';
  p = realpath(path, module->realpath);
  if (p == NULL) {
    return -3;
  }
  module->fd = open(module->realpath, 0);
  if (module->fd < 0) {
    return -3;
  }
  module->realpath_str.start = (u_char *)module->realpath;
  module->realpath_str.length = strlen(module->realpath_str.start);
  return 0;
}