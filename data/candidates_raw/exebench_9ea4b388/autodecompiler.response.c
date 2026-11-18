void merge(int *left, int *right, int *array){
 int *end_left = left + 5;
 int *end_right = right + 5;

 while(1){
  if(*left <= *right){
   if(left == end_left){
    *array = *right;
    array++;
    while(right < end_right){
     *array = *right;
     right++;
     array++;
    }
    return;
   }
   else{
    *array = *left;
    left++;
    array++;
   }
  }
  else{
   if(right == end_right){
    *array = *left;
    array++;
    while(left < end_left){
     *array = *left;
     left++;
     array++;
    }
    return;
   }
   else{
    *array = *right;
    right++;
    array++;
   }
  }
 }
}