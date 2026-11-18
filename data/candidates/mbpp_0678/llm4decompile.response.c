char* func0(char* str1){
 int i=0,j=0;
 int len = strlen(str1);
 while(i<len){
  if(str1[i]!=' '){
   str1[j++] = str1[i];
  }
  i++;
 }
 str1[j] = '\0';
 return str1;
}