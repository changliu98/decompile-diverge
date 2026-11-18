char *Q_strupr(char *s1) {
 char *cp;

 for (cp = s1 ; *cp ; ++cp) {
  if (('a' <= *cp) && (*cp <= 'z')) {
   *cp += 'A' - 'a';
  }
 }

 return s1;
}