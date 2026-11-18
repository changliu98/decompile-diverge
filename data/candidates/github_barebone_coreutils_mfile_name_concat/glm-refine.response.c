char *__cdecl mfile_name_concat(const char *dir, const char *base, char **base_in_result)
{
  char *p;
  char *p_concat;
  char sep;
  size_t baselen;
  size_t dirlen;
  size_t dirbaselen;
  char *dirbase;

  // Get the last component of the directory path and its length
  dirbase = last_component(dir);
  dirbaselen = base_len(dirbase);
  
  // Calculate the total length of the directory portion to copy
  dirlen = dirbaselen + (dirbase - dir);
  baselen = strlen(base);
  
  sep = 0;
  
  // Determine if a separator character is needed between dir and base
  if (dirbaselen)
  {
    // If neither the end of dir nor the start of base has '/', we need a '/'
    if (dirbase[dirbaselen - 1] != '/' && *base != '/')
      sep = '/';
  }
  else if (*base == '/')
  {
    // If dir is empty but base starts with '/', prepend a '.' to make it a relative path
    sep = '.';
  }
  
  // Allocate memory: dir length + separator (if any) + base length + null terminator
  p_concat = (char *)malloc(dirlen + (sep != 0) + baselen + 1);
  if (!p_concat)
    return NULL;
    
  // Copy the directory portion
  memcpy(p_concat, dir, dirlen);
  
  // Add the separator if one was determined
  p_concat[dirlen] = sep;
  
  // Calculate the pointer to where the base string will start
  p = &p_concat[dirlen + (sep != 0)];
  
  // If the caller requested it, return the pointer to the base string within the new buffer
  if (base_in_result)
    *base_in_result = p;
    
  // Copy the base string and null-terminate the result
  memcpy(p, base, baselen);
  p[baselen] = '\0';
  
  return p_concat;
}