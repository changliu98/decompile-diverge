void func0(int *arr,int size,int number)

{
  int iVar1;
  int temp;
  int j;
  int i;
  int number_local;
  int size_local;
  int *arr_local;
  
  for (i = 0; i < size + -1; i = i + 1) {
    for (j = 0; j < (size - i) + -1; j = j + 1) {
      if (arr[j + 1] < arr[j]) {
        iVar1 = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = iVar1;
      }
    }
  }
  if (arr[size + -1] < number) {
    printf("Yes, the entered number is greater than those in the array\n");
  }
  else {
    printf("No, entered number is less than those in the array\n");
  }
  return;
}