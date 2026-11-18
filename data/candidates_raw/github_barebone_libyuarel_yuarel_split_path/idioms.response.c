int path_split(char *path, char **parts, int max_parts)
{
  char *p = path;
  int i = 0;
  if (!p || !*p)
    return -1;
  do {
    while (*p == '/')
      p++;
    if (!*p)
      break;
    parts[i++] = p;
    if (i >= max_parts)
      break;
    p = strchr(p, '/');
    if (!p)
      break;
    *p++ = '\0';
  } while (1);
  return i;
}