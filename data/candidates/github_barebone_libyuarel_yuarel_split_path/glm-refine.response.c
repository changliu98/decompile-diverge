int __cdecl yuarel_split_path(char *path, char **parts, int max_parts)
{
  int i = 0;
  char *curr;

  if (!path || !*path)
    return -1;

  curr = path;
  
  do
  {
    // Skip leading slashes
    while (*curr == '/')
      curr++;

    // Break if we've reached the end of the string
    if (!*curr)
      break;

    // Store the start of the current path segment
    parts[i++] = curr;

    // Find the next slash
    curr = strchr(curr, '/');
    
    // If no more slashes are found, we are done
    if (!curr)
      break;

    // Terminate the current segment and move to the next character
    *curr = '\0';
    curr++;
  }
  while (i < max_parts);

  return i;
}