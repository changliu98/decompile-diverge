char *get_longest(char **argv, int argc)
{
 char *longest = "\0";
 int longest_len = 0;
 int i, len;

 for (i = 0; ; i++) {
  if (i >= argc) break;
  len = strlen(argv[i]);
  if (len > longest_len) {
   longest = argv[i];
   longest_len = len;
  }
 }

 return longest;
}