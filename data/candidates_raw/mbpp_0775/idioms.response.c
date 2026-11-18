int is_even(int *nums, int size){
  int i;
  for(i = 0; i < size; i++){
    if(nums[i]%2 != i%2){
      return 0;
    }
  }
  return 1;
}