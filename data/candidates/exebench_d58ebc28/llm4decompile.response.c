void dummyfunc(char *s)
{
 int i;
 char *t;
 static char s_Goodbye[] = "Goodbye!";

 t = s_Goodbye;
 for (i = 0; s[i] != '\0'; i++)
  s[i] = t[i];
}