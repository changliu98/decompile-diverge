int is_isomorphic(char **list1, char **list2, int size1, int size2){
  char **ordered_list1 = list1;
  char **ordered_list2 = list2;
  int size1_ = size1;
  int size2_ = size2;
  int i; int j;
  int common_elements_size = 0;
  char *common_elements[-1];
  for(i = 0; i < size1_; i++){
    for(j = 0; j < size2_; j++){
      if(strcmp(ordered_list1[i], ordered_list2[j]) == 0){
        int is_unique = 1;
        for(int k = 0; k < common_elements_size; k++){
          if(strcmp(common_elements[k], ordered_list1[i]) == 0){
            is_unique = 0;
            break;
          }
        }
        if(is_unique){
          common_elements[common_elements_size++] = ordered_list1[i];
        }
      }
    }
  }
  int index1 = 0;
  int index2 = 0;
  char *ordered_list1[-1];
  char *ordered_list2[-1];
  for(i = 0; i < size1_; i++){
    for(j = 0; j < common_elements_size; j++){
      if(strcmp(ordered_list1[i], common_elements[j]) == 0){
        ordered_list1[index1++] = ordered_list1[i];
      }
    }
  }
  for(i = 0; i < size2_; i++){
    for(j = 0; j < common_elements_size; j++){
      if(strcmp(ordered_list2[i], common_elements[j]) == 0){
        ordered_list2[index2++] = ordered_list2[i];
      }
    }
  }
  if(index1 != index2){
    return 0;
  }
  for(i = 0; i < index1; i++){
    if(strcmp(ordered_list1[i], ordered_list2[i]) != 0){
      return 0;
    }
  }
  return 1;
}