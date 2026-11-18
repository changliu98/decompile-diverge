double func0(int *lst,int len)

{
  int i;
  int sum;
  int len_local;
  int *lst_local;
  
  sum = 0;
  for (i = 0; i < len; i = i + 1) {
    sum = lst[i] + sum;
  }
  return (double)sum / (double)len;
}