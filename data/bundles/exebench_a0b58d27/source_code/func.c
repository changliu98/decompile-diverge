
char * string_copy(char * dest, const char * a){
 char *s, *d;
 if(!a || !dest) return 0;
 for(s = (char*) a, d=dest; *s; *d++ = *s++);
 *d = 0;
 return dest;
}
