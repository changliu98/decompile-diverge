int last_slash(char *path, int *number_found, int *path_size)
{
 int i;
 int found;
 int lasti;

 i = 0;
 found = 0;
 lasti = 0;
 while (path[i] != '\0' && i < 256)
 {
  if (path[i] == '/')
  {
   found++;
   lasti = i;
  }
  i++;
 }
 *number_found = found;
 *path_size = i;
 return (lasti);
}