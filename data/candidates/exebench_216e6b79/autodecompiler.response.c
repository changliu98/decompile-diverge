void unescape(char s[], char t[])
{
 int i,j;
 for(i=0,j=0;;i++,j++)
 {
  if(t[i] == '\0')
  {
   s[j]='\0';
   break;
  }
  else if(t[i] == '\\')
  {
   switch(t[++i])
   {
    case 'a':
     s[j] = '\a';
     break;
    case 'b':
     s[j] = '\b';
     break;
    case 'f':
     s[j] = '\f';
     break;
    case 'n':
     s[j] = '\n';
     break;
    case 'r':
     s[j] = '\r';
     break;
    case 't':
     s[j] = '\t';
     break;
    case 'v':
     s[j] = '\v';
     break;
    case '\?':
     s[j] = '\?';
     break;
    case '\\':
     s[j] = '\\';
     break;
    case '\'':
     s[j] = '\'';
     break;
    case '\"':
     s[j] = '\"';
     break;
    default:
     s[j++] = '\\';
     s[j] = t[i];
   }
  }
  else
   s[j]=t[i];
 }
}