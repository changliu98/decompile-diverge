char *__cdecl get_next_file(FILE *VFile, char *ptr)
{
  char *ret; // [rsp+10h] [rbp-20h]

  ret = fgets(ptr, 1024, VFile);
  if ( !ret )
    return 0LL;
  if ( ptr[strlen(ptr) - 1] == 10 )
    ptr[strlen(ptr) - 1] = 0;
  return ret;
}