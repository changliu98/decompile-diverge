int func0(int *num,int size)

{
  int i;
  int count_elim;
  int size_local;
  int *num_local;
  
  count_elim = 0;
  for (i = 0; (i < size && (num[i] != -1)); i = i + 1) {
    count_elim = count_elim + 1;
  }
  return count_elim;
}