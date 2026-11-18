_Bool func0(char **l1,char **l2,int size1,int size2)

{
  bool bVar1;
  int iVar2;
  int i_3;
  int j_2;
  int i_2;
  int j_1;
  int i_1;
  char *ordered_l2 [100];
  char *ordered_l1 [100];
  int index2;
  int index1;
  int k;
  _Bool is_unique;
  int j;
  int i;
  char *common_elements [100];
  int common_elements_size;
  int size2_local;
  int size1_local;
  char **l2_local;
  char **l1_local;
  _Bool local_9;
  
  common_elements_size = 0;
  i = 0;
  do {
    if (size1 <= i) {
      index1 = 0;
      index2 = 0;
      for (i_1 = 0; i_1 < size1; i_1 = i_1 + 1) {
        for (j_1 = 0; j_1 < common_elements_size; j_1 = j_1 + 1) {
          iVar2 = strcmp(l1[i_1],common_elements[j_1]);
          if (iVar2 == 0) {
            ordered_l1[index1] = l1[i_1];
            index1 = index1 + 1;
          }
        }
      }
      for (i_2 = 0; i_2 < size2; i_2 = i_2 + 1) {
        for (j_2 = 0; j_2 < common_elements_size; j_2 = j_2 + 1) {
          iVar2 = strcmp(l2[i_2],common_elements[j_2]);
          if (iVar2 == 0) {
            ordered_l2[index2] = l2[i_2];
            index2 = index2 + 1;
          }
        }
      }
      if (index1 == index2) {
        for (i_3 = 0; i_3 < index1; i_3 = i_3 + 1) {
          iVar2 = strcmp(ordered_l1[i_3],ordered_l2[i_3]);
          if (iVar2 != 0) {
            return false;
          }
        }
        local_9 = true;
      }
      else {
        local_9 = false;
      }
      return local_9;
    }
    for (j = 0; j < size2; j = j + 1) {
      iVar2 = strcmp(l1[i],l2[j]);
      if (iVar2 == 0) {
        bVar1 = true;
        for (k = 0; k < common_elements_size; k = k + 1) {
          iVar2 = strcmp(common_elements[k],l1[i]);
          if (iVar2 == 0) {
            bVar1 = false;
            break;
          }
        }
        if (bVar1) {
          common_elements[common_elements_size] = l1[i];
          common_elements_size = common_elements_size + 1;
        }
      }
    }
    i = i + 1;
  } while( true );
}