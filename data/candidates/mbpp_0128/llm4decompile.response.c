char ** func0(int n, char * str, int * count){
 char * p;
 int i=0;
 p = strtok(str, " ");
 while(p!=NULL){
  if(strlen(p)>n){
   func0::word_len[i]=p;

   i++;
  }
  p = strtok(NULL, " ");
 }
 *count = i;
 return func0::word_len;

}