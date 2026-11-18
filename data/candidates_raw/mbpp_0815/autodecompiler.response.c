void sort(int *a,int len){
 int i,j=0,k=len-1,temp;
 while(1){
  if(j>k)
   return ;
  if(a[j]==0){
   temp=a[i];
   a[i]=a[j];
   a[j]=temp;
   i++;
   j++;
  }else if(a[j]==1){
   j++;
  }else{
   temp=a[j];
   a[j]=a[k];
   a[k]=temp;
   k--;
  }
 }
}