static char * envstring(char *str){
 char *s;
 for(s = str; *s; s++){
  if(*s == '-')
   *s = '_';
  else if((*s >= 'a') && (*s <= 'z'))
   *s -= 'a' - 'A';
  else if((*s < 'A') || (*s > 'Z')){
   *str = 0;
   break;
  }
 }

 return str;
}