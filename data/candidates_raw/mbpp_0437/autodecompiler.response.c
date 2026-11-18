char* func0(char* str){
 int i;
 int j = 0;
 for(i = 1; ; i++){
  size_t len = strlen(str);
  if(i > len) break;
  if(i%2 == 0){
   func0_str2[j++] = str[i-1];
  }
 }
 func0_str2[j] = '\0';
 return func0_str2;
}