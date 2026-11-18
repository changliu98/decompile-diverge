char* func0(char* str) {
 int i;
 int j = 0;
 for(i = 0;; i++) {
  if(i >= strlen(str)) {
   break;
  }
  if(i % 2 == 0) {
   func0_result[j++] = str[i];
  }
 }
 func0_result[j] = '\0';
 return func0_result;
}