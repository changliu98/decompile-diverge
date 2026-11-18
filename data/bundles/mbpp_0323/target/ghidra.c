void func0(int *arr,int n)

{
  int index;
  int out_of_place;
  int n_local;
  int *arr_local;
  
  out_of_place = -1;
  for (index = 0; index < n; index = index + 1) {
    if ((-1 < out_of_place) &&
       (((-1 < arr[index] && (arr[out_of_place] < 0)) ||
        ((arr[index] < 0 && (-1 < arr[out_of_place])))))) {
      right_rotate(arr,n,out_of_place,index);
      if (index - out_of_place < 3) {
        out_of_place = -1;
      }
      else {
        out_of_place = out_of_place + 2;
      }
    }
    if ((out_of_place == -1) &&
       (((-1 < arr[index] && (index % 2 == 0)) || ((arr[index] < 0 && (index % 2 == 1)))))) {
      out_of_place = index;
    }
  }
  return;
}