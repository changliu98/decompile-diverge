char* func0(char* str) {
 int i, j;
 j = 0;
 for(i = 0; ; i++) {
  if(i >= strlen(str)) break;
  if(((*___ctype_b_loc ())[(int) ((str[i]))] & (unsigned short int) 0x0008)) {
   func0_result[j++] = str[i];
  }
 }
 func0_result[j] = '\0';
 return func0_result;
}