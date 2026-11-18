void sort(char *c){
 int i,j;
 char temp;
 for(i=1;i<11;i++){
  for(j=0;j<11 -i;j++){
   if((j>=11 -i-1 ? 0 : *(c+j)) && (*(c+j)>*(c+j+1) ? 1 : 0)){
    temp = *(c+j);
    *(c+j)=*(c+j+1);
    *(c+j+1)=temp;
   }
  }
 }
}