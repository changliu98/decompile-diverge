void __cdecl file_perms_get(const unsigned char *path, int *p_group, int *p_mode)
{
  struct stat stb;

  // Reset output parameters if they are non-NULL/non-zero
  if (p_group && *p_group)
    *p_group = 0;
    
  if (p_mode && *p_mode)
    *p_mode = 0;

  // Retrieve file statistics
  if (stat((const char *)path, &stb) >= 0)
  {
    if (p_group)
      *p_group = stb.st_gid;
      
    if (p_mode)
      *p_mode = stb.st_mode & 07777; // 0xFFF in hex is 4095 in dec, equivalent to 07777 in octal
  }
}