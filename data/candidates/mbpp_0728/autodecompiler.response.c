void func0(int *list1, int *list2, int *res_list, int size){
  int i = 0;
  while(1){
    if(i >= size) break;
    res_list[i] = list1[i] + list2[i];
    i++;
  }
}