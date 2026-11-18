_Bool func0(int *lst,int lst_size)

{
  int i;
  int lst_size_local;
  int *lst_local;
  
  if (lst_size != 0) {
    for (i = 1; i < lst_size; i = i + 1) {
      if (lst[i] < lst[i + -1]) {
        return false;
      }
      if (((1 < i) && (lst[i] == lst[i + -1])) && (lst[i] == lst[i + -2])) {
        return false;
      }
    }
  }
  return true;
}