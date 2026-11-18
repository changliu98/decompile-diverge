void toUpperCase(char *string) {
 int i, j;
 char c;
 for(i = 0; string[i] != '\0'; i++) {
  for(c = 'a', j = 0; c <= 'z'; c++, j++) {
   if(string[i] == c) {
    string[i] -= 32;
   }
  }
 }
}