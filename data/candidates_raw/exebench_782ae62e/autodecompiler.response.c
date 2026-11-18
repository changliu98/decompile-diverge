void str_to_upper(char *str) {
 int i = 0;
 while(1) {
  if(str[i] == '\0') {
   break;
  }
  if(str[i] >= 'a' && str[i] <= 'z') {
   str[i] -= ('a' - 'A');
  }
  i++;
 }
}