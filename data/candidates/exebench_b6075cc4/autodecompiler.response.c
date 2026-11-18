void break_atr(char *s, char c)
{
char *p;

if ((p = strrchr(s,c)) != NULL) *p = '\0';
}