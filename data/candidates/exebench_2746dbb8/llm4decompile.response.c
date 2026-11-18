void _uc(char *str)
{
  char *pt;

  for (pt = str; *pt; pt++)
    if (*pt >= 'a' && *pt <= 'z')
      *pt -= 'a' - 'A';
}