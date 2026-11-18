void func0(int *arr,int n)

{
  int end;
  int max_idx;
  int curr_size;
  int n_local;
  int *arr_local;
  
  for (curr_size = n; 1 < curr_size; curr_size = curr_size + -1) {
    end = find_max_index(arr,curr_size);
    if (end != curr_size + -1) {
      reverse(arr,0,end);
      reverse(arr,0,curr_size + -1);
    }
  }
  return;
}