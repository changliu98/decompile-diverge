char* func0(char* str){
 static char func0_str2[1024];
 int i, j = 0;
 for(i = 1; ; i++){
  if(i > strlen(str)) break;
  if(i%2 != 0) func0_str2[j++] = str[i-1];
 }
 func0_str2[j] = '\0';
 return func0_str2;
}