int last_slash(const char *path, int *number_found, int *path_size)
{
   int i, found=0, lasti=0;


   for (i=0; path[i] && i<256; i++)
      if (path[i] == '/')
      {
         found++;
         lasti=i;
      }

   *number_found = found;
   *path_size = i;

   return lasti;
}