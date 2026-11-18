char *get_next_file(FILE *VFile, char *ptr)
{
 char *ret;

 ret = fgets(ptr, 1024, VFile);
 if (ret == NULL)
  return NULL;

 if (ptr[strlen(ptr) - 1] == '\n')
  ptr[strlen(ptr) - 1] = '\0';

 return ret;
}