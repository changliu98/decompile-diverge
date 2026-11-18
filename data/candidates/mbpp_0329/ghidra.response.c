int func0(int *list,int list_size)

{
  int i;
  int neg_count;
  int list_size_local;
  int *list_local;
  
  neg_count = 0;
  for (i = 0; i < list_size; i = i + 1) {
    if (list[i] < 1) {
      neg_count = neg_count + 1;
    }
  }
  return neg_count;
}