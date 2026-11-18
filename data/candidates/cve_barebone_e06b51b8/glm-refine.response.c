char *__cdecl uwsgi_expand_path(char *dir, int dir_len, char *ptr)
{
  char src[4097]; 
  char *dst;
  
  // Safely copy the directory path to a local null-terminated buffer
  memcpy(src, dir, dir_len);
  src[dir_len] = '\0';
  
  // Determine the destination buffer: use provided pointer or allocate 4097 bytes
  dst = ptr;
  if (!ptr) {
    dst = (char *)uwsgi_malloc(0x1001uLL);
  }
  
  // Resolve the absolute pathname
  if (realpath(src, dst)) {
    return dst;
  }
  
  // Log the error if realpath fails
  uwsgi_log(
    "realpath() of %s failed: %s [%s line %d]\n", 
    src, 
    strerror(errno), 
    "/work/harness.c", 
    65
  );
  
  // Free the allocated buffer if we created it
  if (!ptr) {
    free(dst);
  }
  
  return NULL;
}