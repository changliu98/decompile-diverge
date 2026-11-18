static char* skip(char *s, char c) {
 while(*s != c && *s != '\0')
  s++;
 if(*s != '\0')
  *s++ = '\0';
 return s;
}