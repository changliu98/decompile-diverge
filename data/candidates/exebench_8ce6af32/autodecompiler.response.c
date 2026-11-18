int endStrider(char *str, int *index)
{
 *index = 0;
 return (strstr(str, "//") != NULL) ? 1 : 0;
}