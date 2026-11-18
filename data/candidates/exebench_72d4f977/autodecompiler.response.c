int endGB(char *line, int *ret)
{
 char locus_tag[512];
 char *ptr;
 int i;

 *ret = 0;

 if ((ptr = strstr(line, "//")) != NULL) {
  return(1);
 }

 if (strstr(line, "LOCUS") == line) {
  return(1);
 }
 else {
  return(0);
 }
}