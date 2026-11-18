char* func0(char *str, char c) {
 int len = strlen(str);
 int first = -1, last = -1;
 for(int i=0;i<len;i++) {
  if(str[i] == c) {
   if(first == -1)
    first = i;
   last = i;
  }
 }
 if(first != -1 && last != -1 && first != last) {
  char *newStr = malloc(sizeof(char)*(len-2+1));
  int index = 0;
  for(int i=0;i<first;i++)
   newStr[index++] = str[i];
  for(int i=first+1;i<last;i++)
   newStr[index++] = str[i];
  for(int i=last+1;i<len;i++)
   newStr[index++] = str[i];
  newStr[index] = '\0';
  return newStr;
 } else {
  char *newStr = malloc(sizeof(char)*(len+1));
  strcpy(newStr, str);
  return newStr;
 }
}