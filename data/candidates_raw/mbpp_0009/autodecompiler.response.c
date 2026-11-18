int getNext(char *pattern){
 int pLen = strlen(pattern);
 char pat[pLen*2+1];
 strcpy(pat,pattern);
 strcat(pat,pattern);

 int i=1;
 while(i<=pLen){
  int j = 0;
  int flag = 1;
  while(j<pLen){
   if(pat[i+j] != pattern[j]){
    flag = 0;
    break;
   }
   j++;
  }
  if(flag){
   return i;
  }
  i++;
 }
 return pLen;
}