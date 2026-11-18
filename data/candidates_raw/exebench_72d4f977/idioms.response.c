int is_fasta(char *line, int *addend)
{
  char *str;
  *addend = 0;
  str = strstr(line,"//");
  if (str == ((void *)0))
    str = strstr(line,"LOCUS");
  if (str == line)
    return 1;
  return 0;
}