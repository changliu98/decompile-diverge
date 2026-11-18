char **__cdecl func0(const char *str, int *count)
{
  int len = strlen(str);
  
  // Allocate an array of string pointers (Note: allocates 8 * len bytes, 
  // which is technically 1 pointer short if the string is completely full, 
  // but matches the original assembly's semantics).
  char **out = (char **)malloc(8LL * len);
  
  // Buffer to hold the progressively building string
  char *current = (char *)malloc(len + 1);
  current[0] = '\0';
  
  int current_len = 0;

  for (int i = 0; i < len; ++i)
  {
    // Append the next character from str to current
    current[current_len] = str[i];
    current[current_len + 1] = '\0';
    current_len++;

    // Duplicate the current prefix into the output array
    out[i] = (char *)malloc(current_len + 1);
    strcpy(out[i], current);
  }
  
  free(current);
  *count = len;
  
  return out;
}