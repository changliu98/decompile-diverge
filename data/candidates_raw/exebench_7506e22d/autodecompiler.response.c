void upcase(char *c)
{
 char upcas_diff = 'A' - 'a';
 if (*c >= 'a' && *c <= 'z')
  *c += upcas_diff;
}