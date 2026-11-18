int filter_files(char **files, int num_files, char *search, char ***results)
{
 int i, j, k;
 int len = strlen(search);

 *results = (char **) malloc(num_files * sizeof(char *));

 for (j = 0, i = 0; ; i++) {
  if (i >= num_files)
   break;

  if (!strncmp(files[i], search, len))
   (*results)[j++] = files[i];

 }

 return j;
}