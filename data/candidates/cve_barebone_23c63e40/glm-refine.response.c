char *__cdecl get_next_file(FILE *VFile, char *ptr)
{
  char *ret;
  size_t len;

  // Read the next line from the file (up to 1023 chars + null terminator)
  ret = fgets(ptr, 1024, VFile);
  if (!ret)
    return NULL;

  // Strip the trailing newline character ('\n' == 10) if it exists
  len = strlen(ptr);
  if (len > 0 && ptr[len - 1] == '\n')
    ptr[len - 1] = '\0';

  return ret;
}