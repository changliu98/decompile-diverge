void func0(char *text)
{
 char *in, *out;

 in = text;
 out = text;
 while (*in != '\0') {
  if (strchr("AEIOUaeiou", *in) == NULL) {
   *out = *in;
   out++;
  }
  in++;
 }
 *out = '\0';
}