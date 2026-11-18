_Bool func0(int *arr,int n,int i)

{
  _Bool local_26;
  _Bool local_25;
  _Bool local_24;
  _Bool local_23;
  _Bool right_child;
  _Bool left_child;
  int i_local;
  int n_local;
  int *arr_local;
  _Bool local_9;
  
  if (n < i * 2 + 2) {
    local_9 = true;
  }
  else {
    local_23 = false;
    if (arr[i] <= arr[i * 2 + 1]) {
      local_23 = func0(arr,n,i * 2 + 1);
    }
    local_24 = true;
    if (i * 2 + 2 != n) {
      local_25 = false;
      if (arr[i] <= arr[i * 2 + 2]) {
        local_25 = func0(arr,n,i * 2 + 2);
      }
      local_24 = local_25;
    }
    local_26 = false;
    if (local_23 != false) {
      local_26 = local_24;
    }
    local_9 = local_26;
  }
  return local_9;
}