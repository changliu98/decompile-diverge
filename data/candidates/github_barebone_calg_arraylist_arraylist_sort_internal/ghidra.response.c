void arraylist_sort_internal
               (ArrayListValue *list_data,uint list_length,ArrayListCompareFunc compare_func)

{
  ArrayListValue pvVar1;
  ArrayListValue pvVar2;
  int iVar3;
  uint list2_length;
  uint list1_length;
  uint i;
  ArrayListValue tmp;
  ArrayListValue pivot;
  ArrayListCompareFunc compare_func_local;
  uint list_length_local;
  ArrayListValue *list_data_local;
  
  if (1 < list_length) {
    pvVar1 = list_data[list_length - 1];
    list1_length = 0;
    for (i = 0; i < list_length - 1; i = i + 1) {
      iVar3 = (*compare_func)(list_data[i],pvVar1);
      if (iVar3 < 0) {
        pvVar2 = list_data[i];
        list_data[i] = list_data[list1_length];
        list_data[list1_length] = pvVar2;
        list1_length = list1_length + 1;
      }
    }
    list_data[list_length - 1] = list_data[list1_length];
    list_data[list1_length] = pvVar1;
    arraylist_sort_internal(list_data,list1_length,compare_func);
    arraylist_sort_internal
              (list_data + (list1_length + 1),(list_length - list1_length) - 1,compare_func);
  }
  return;
}