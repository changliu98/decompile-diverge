int int2arr(int arr[], int num) {

 int i = 0;

 for( ; num != 0 ; num/=10, i++) {

  arr[i] = num%10;

 }

 return i;

}