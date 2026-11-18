void misc_str_remove_symbol(char *string, unsigned char c) {
 char *dest = string;
 int d=0, s=0;

 while(1) {
  if(dest[s] == '\0') {
   dest[d] = '\0';
   return;
  }
  if(dest[s] != c) {
   dest[d] = dest[s];
   d++;
  }
  s++;
 }
}