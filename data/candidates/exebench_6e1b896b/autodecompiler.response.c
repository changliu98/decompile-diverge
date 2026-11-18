void break_at(char *s, char c)
{
 char *end = strchr(s, c);
 if (end) *end = '\0';
}