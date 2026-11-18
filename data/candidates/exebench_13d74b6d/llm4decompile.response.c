void copy(char *longest, char *line)
{
 int i;

 for (i = 0; (longest[i] = line[i]) != '\0'; i++)
  ;
}