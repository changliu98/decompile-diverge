int sum(int arr[], int length){
 int i;
 int sum = 0;

 for(i = 0; i < length; i++){
  if(arr[i] > -100 && arr[i] < 100)
   sum += arr[i];
 }

 return sum;
}