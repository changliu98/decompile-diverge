double func0(double *data_array, int n){

 double second_smallest;
 if(n<3){
  second_smallest = -9999999;
 }
 else{
  int count=0;
  for(int i=0;i<n;i++){
   for(int j=i+1;j<n;j++){
    if(data_array[i]==data_array[j]){
     count++;
    }
   }
  }
  if((n==2)&&(count==1)){
   second_smallest = -9999999;
  }
  else{
   double *unique_items = malloc(n*sizeof(double));
   int u=0;
   for(int i=0;i<n;i++){
    int flag=0;
    for(int j=0;j<u;j++){
     if(unique_items[j]==data_array[i]){
      flag=1;
     }
    }
    if(flag==0){
     unique_items[u++] = data_array[i];
    }
   }

   for(int i=0;i<u;i++){
    for(int j=i+1;j<u;j++){
     if(unique_items[i]>unique_items[j]){
      double temp = unique_items[i];
      unique_items[i] = unique_items[j];
      unique_items[j] = temp;
     }
    }
   }
   second_smallest = unique_items[1];
   free(unique_items);
  }
 }
 return second_smallest;
}