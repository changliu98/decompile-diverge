int cpy(char *dest, char *src){
  int i = 0;
  for(;;i++){
    char c = src[i];
    if(!c){
      dest[i] = '\0';
      return 0;
    }
    if(i >= 100){
      dest[i] = '\0';
      return 0;
    }
    dest[i] = c;
  }
}