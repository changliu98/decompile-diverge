char *strtoupper(char *str){
  int i;
  for(i = 0; i < 8; i++){
    if(str[i] >= 'a' && str[i] <= 'z')
      str[i] = str[i] - 'a' + 'A';
    else
      str[i] = str[i];
  }
  return str;
}