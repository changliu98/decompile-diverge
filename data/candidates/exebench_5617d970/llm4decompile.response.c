int arrayFind(int elem,int *list,int length){
 int i,j;
 for(i=0;i<length;i++){
  if(list[i]==elem){
   for(j=0;j<i;j++){
    list[i-j]=list[i-j-1];
   }
   list[0]=elem;
   return 0;
  }
 }
 return -1;
}