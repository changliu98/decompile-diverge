char *strtoupper(char *str){
 int i = 0;
 for(i = 0; i < 8; i++){
  if(str[i] >= 'a' && str[i] <= 'z'){
   str[i] = str[i] - 32;
  }
  else{
   str[i] = str[i];
  }
 }
 return str;
}