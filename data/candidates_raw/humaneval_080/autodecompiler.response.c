int check(char word[100]){

 int flag;
 if(strlen(word) < 4){
  flag = 0;
 }
 else{
  int i;
  for(i = 2; ; i++){
   if(i >= strlen(word)){
    flag = 1;
    break;
   }
   if((word[i] == word[i-1]) || (word[i] == word[i-2])){
    flag = 0;
    break;
   }
  }
 }

 return flag&1;
}