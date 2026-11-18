int get_xor(int *arr, int n){
 int i; int j; int res = 0;
 for(i=0; i<n; i++){
  for(j=i+1; j<n; j++){
   res += (arr[i] ^ arr[j]);
  }
 }
 return res;
}