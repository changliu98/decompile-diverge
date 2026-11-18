int get_min(int *list, int size){
  int i;
  for (i = 0; i < size; i++)
    if (list[i] < 0)
      return list[i];
  return 0;
}