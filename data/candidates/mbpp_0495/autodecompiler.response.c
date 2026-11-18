char* func0(char* str) {
 int i = 0;
 int j = 0;
 while(1) {
  switch(str[j]) {
   case '\0':
    func0_result[i] = '\0';
    return func0_result;
   default:
    if(str[j] < 97 || str[j] > 122) {
     func0_result[i++] = str[j];
    }
    break;
  }
  j++;
 }
}