int yuarel_split_path(char *path, char **parts, int max_parts) {
 int count = 0;
 char *ch;

 if (!path || !*path)
  return -1;

 while (1) {
  while (*path == '/')
   ++path;

  if (!*path)
   break;

  parts[count++] = path;

  ch = strchr(path, '/');
  if (!ch)
   break;

  *ch = '\0';
  path = ch + 1;

  if (count >= max_parts)
   break;
 }

 return count;
}