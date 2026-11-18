int func0(int *lst,int size)

{
  int i;
  int second;
  int first;
  int size_local;
  int *lst_local;
  int local_c;
  
  if (size < 2) {
    local_c = -1;
  }
  else {
    first = 0x7fffffff;
    second = 0x7fffffff;
    for (i = 0; i < size; i = i + 1) {
      if (lst[i] < first) {
        second = first;
        first = lst[i];
      }
      else if ((lst[i] < second) && (lst[i] != first)) {
        second = lst[i];
      }
    }
    if (second == 0x7fffffff) {
      local_c = -1;
    }
    else {
      local_c = second;
    }
  }
  return local_c;
}