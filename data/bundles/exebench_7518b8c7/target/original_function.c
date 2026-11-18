int max(float arr[]){
 int i, ret=0;
 float highest=arr[0];
 for(i=0; i<(sizeof(arr)/sizeof(float)); i++){
  if(arr[i]>highest){
   ret=i;
   highest=arr[i];
  }
 }
 return ret;
}