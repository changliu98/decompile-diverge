int
yuarel_split_path(char *path, char **parts, int max_parts)
{
 int nbParts = 0;
 int ret;

 if (path == NULL || path[0] == '\0') {
  ret = -1;
  goto end;
 }

 do {

  while (*path == '/') {
   path++;
  }

  if (*path == '\0') {
   break;
  }


  parts[nbParts++] = path;


  path = strchr(path, '/');
  if (path == NULL) {
   break;
  }


  *(path++) = '\0';
 } while (nbParts < max_parts);

 ret = nbParts;

end:
 return ret;
}