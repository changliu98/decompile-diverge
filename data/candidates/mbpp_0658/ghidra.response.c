int func0(int *list1,int length)

{
  int j;
  int occu;
  int i;
  int result;
  int max_val;
  int length_local;
  int *list1_local;
  
  max_val = 0;
  result = *list1;
  for (i = 0; i < length; i = i + 1) {
    occu = 0;
    for (j = 0; j < length; j = j + 1) {
      if (list1[j] == list1[i]) {
        occu = occu + 1;
      }
    }
    if (max_val < occu) {
      max_val = occu;
      result = list1[i];
    }
  }
  return result;
}