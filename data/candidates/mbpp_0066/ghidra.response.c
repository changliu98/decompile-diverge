int func0(int *list,int list_size)

{
  int i;
  int pos_count;
  int list_size_local;
  int *list_local;
  
  pos_count = 0;
  for (i = 0; i < list_size; i = i + 1) {
    if (-1 < list[i]) {
      pos_count = pos_count + 1;
    }
  }
  return pos_count;
}