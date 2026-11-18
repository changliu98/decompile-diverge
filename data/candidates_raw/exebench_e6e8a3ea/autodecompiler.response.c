int
get_directory_count(char *path, int *dir_count, int *len)
{
 int i, lasti, found;

 found = 0;
 lasti = 0;
 for (i = 0;; i++) {
  if (!((path[i] != '\0') && (i < 256)))
   break;
  if (path[i] == '/') {
   found++;
   lasti = i;
  }
 }

 *dir_count = found;
 *len = i;
 return(lasti);
}