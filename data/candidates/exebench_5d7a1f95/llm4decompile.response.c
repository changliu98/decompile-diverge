void escape(char *s, char *t)
{
 int i,j;
 for(i=0,j=0;t[i]!='\0';i++,j++){
  switch(t[i]){
   case '\a':s[j]='\\';j++;s[j]='a';break;
   case '\b':s[j]='\\';j++;s[j]='b';break;
   case '\t':s[j]='\\';j++;s[j]='t';break;
   case '\n':s[j]='\\';j++;s[j]='n';break;
   case '\v':s[j]='\\';j++;s[j]='v';break;
   case '\f':s[j]='\\';j++;s[j]='f';break;
   case '\r':s[j]='\\';j++;s[j]='r';break;
   case '\\':s[j]='\\';j++;s[j]='\\';break;
   case '\'':s[j]='\\';j++;s[j]='\'';break;
   case '\"':s[j]='\\';j++;s[j]='\"';break;
   case '\?':s[j]='\\';j++;s[j]='\?';break;
   default :s[j]=t[i];break;
  }
 }
 s[j]='\0';
}