void func0(int *lst,int size,int *result)

{
  int i;
  int minpos;
  int maxneg;
  int *result_local;
  int size_local;
  int *lst_local;
  
  maxneg = 0;
  minpos = 0;
  for (i = 0; i < size; i = i + 1) {
    if ((lst[i] < 0) && ((maxneg == 0 || (maxneg < lst[i])))) {
      maxneg = lst[i];
    }
    if ((0 < lst[i]) && ((minpos == 0 || (lst[i] < minpos)))) {
      minpos = lst[i];
    }
  }
  *result = maxneg;
  result[1] = minpos;
  return;
}