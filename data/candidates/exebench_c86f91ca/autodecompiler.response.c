void remove_dupc2(char* str){
 int i, j, k;
 char flag;

 for(k = 0; ;k++){
  if(str[k] == '\0') break;
  if(str[k] == -1) continue;

  for(j = k+1; ;j++){
   if(str[j] == '\0') break;
   if(str[k] == str[j]){
    str[j] = -1;
   }
  }
 }

 for(j = 0, flag = 0; ;j++){
  if(str[j] == '\0' && flag == 0) break;
  if(str[j] == -1) continue;
  flag = 1;
 }

 if(str[j] == '\0') k--;

 for(i = k+1, j = k+1; ;j++){
  if(str[j] == '\0') break;
  if(str[j] != -1){
   str[i++] = str[j];
  }
 }
 str[i] = str[j];
}