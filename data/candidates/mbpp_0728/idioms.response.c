void func0(int *list1, int *list2, int *res_list, int size){
  int i;
  for(i = 0; i < size; i++)
    res_list[i] = list1[i] + list2[i];
}