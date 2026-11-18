_Bool func0(int *arr,int size)

{
  int i;
  int num;
  int size_local;
  int *arr_local;
  _Bool local_9;
  
  num = 0;
  if (size == 0) {
    local_9 = true;
  }
  else {
    for (i = 1; i < size; i = i + 1) {
      if (arr[i] < arr[i + -1]) {
        num = num + 1;
      }
    }
    if (*arr < arr[size + -1]) {
      num = num + 1;
    }
    if (num < 2) {
      local_9 = true;
    }
    else {
      local_9 = false;
    }
  }
  return local_9;
}