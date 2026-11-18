static int
lookup(char *name, char **table, char *values, size_t vsize)
{
 size_t len = strlen(name);
 long matchind = -1;
 int ambiguous = 0;
 long i;
 long result;

 for (i = 0;; i++) {
  if (table[i] == NULL) {
   if (ambiguous)
    result = -2;
   else
    result = matchind;
   break;
  }
  if (strncmp(table[i], name, len) != 0)
   continue;
  if (strlen(table[i]) == len) {
   result = i;
   break;
  }
  if (matchind == -1)
   matchind = i;
  else if ((values == NULL) ||
      memcmp(values + vsize * matchind,
      values + vsize * i, vsize)) {
   ambiguous = 1;
  }
 }
 return (result);
}