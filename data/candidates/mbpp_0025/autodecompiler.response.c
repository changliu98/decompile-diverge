int func0(int *list,int m){
 int p=1;
 int i,j,k;
 for(i=1;i<m;i++){
  k=list[i];
  j=i-1;
  while(j>=0 && list[j]>k){
   list[j+1]=list[j];
   j--;
  }
  list[j+1]=k;
 }
 for(i=0;i<m;i++){
  if((i==0) || (list[i-1]!=list[i]))
   p=p*list[i];
 }
 return p;
}