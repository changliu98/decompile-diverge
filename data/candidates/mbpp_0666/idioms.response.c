int func0(char *str, char c){
  int i;
  int count = 0;
  for(i = 0; i < strlen(str); i++){
    if(str[i] == c){
      count++;
    }
  }
  return count;
}