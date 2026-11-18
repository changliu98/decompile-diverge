int str_linecount(char *s, int col, int *i)
{
 int line;

 for (line = 1;; s++) {
  if (*s == '\0')
   return line;
  else if (*s == '\n') {
   line++;
   *i = 0;
  } else {
   (*i)++;
   if (*i >= col) {
    line++;
    *i = 0;
   }
  }
 }
}