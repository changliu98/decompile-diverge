















int add_char_to_string(char *const string, char c, const int size) {
 int i;


 if ( !string ) {
  return 0;
 }


 for ( i = 0; string[i]; i++ );


 if ( i >= size-1 ) {
  return 0;
 }


 string[i] = c;
 string[i+1] = '\0';


 return 1;
}
