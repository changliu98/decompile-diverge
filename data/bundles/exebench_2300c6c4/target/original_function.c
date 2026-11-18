static char *strtoupper( char *s ){
 int i, len = sizeof(s);
 for( i = 0; i < len; i++ ){
  s[i] = ( s[i] >= 'a' && s[i] <= 'z' ? s[i] + 'A' - 'a' : s[i] );
 }
 return(s);
}