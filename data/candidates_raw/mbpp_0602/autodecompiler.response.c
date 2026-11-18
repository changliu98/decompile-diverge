int firstSingle(char *string){
 int length = strlen(string);
 char single;
 for(int i=0;i<length;i++){
  char currentChar = string[i];
  int count = 0;
  for(int j=0;j<=i;j++){
   if(string[j] == currentChar)
    count++;
  }
  if(count > 1){
   single = currentChar;
   break;
  }
 }
 return single;
}