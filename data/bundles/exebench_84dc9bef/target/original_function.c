void trim(char *str){
 int i=0;
 for(;;){
  if(str[i]=='\0'){
   str[i-1]='\0';
   return;
  }
  i++;
 }
}