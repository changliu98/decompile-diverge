void unescape(char *s, char *t)
{
 int i, j;

 for (i = j = 0; t[i] != '\0'; i++) {
  if (t[i] == '\\') {
   i++;
   switch (t[i]) {
   case '\\': s[j] = '\\'; break;
   case '\'': s[j] = '\''; break;
   case '"': s[j] = '"'; break;
   case '?': s[j] = '\?'; break;
   case 'a': s[j] = '\a'; break;
   case 'b': s[j] = '\b'; break;
   case 'f': s[j] = '\f'; break;
   case 'n': s[j] = '\n'; break;
   case 'r': s[j] = '\r'; break;
   case 't': s[j] = '\t'; break;
   case 'v': s[j] = '\v'; break;
   default:
    s[j++] = '\\';
    s[j] = t[i];
    break;
   }
  } else {
   s[j] = t[i];
  }
  j++;
 }
 s[j] = '\0';
}