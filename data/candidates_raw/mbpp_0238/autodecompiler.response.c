int calculate(char *s)
{
 int len = strlen(s);
 return len * (len + 1) / 2;
}