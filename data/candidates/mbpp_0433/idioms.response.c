void func0(int a[], int size, int number){
  int i; int j;
  int temp;
  for(i = 0; i < size - 1; i++){
    for(j = 0; j < size - i - 1; j++){
      if(a[j] > a[j + 1]){
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }
  if(number > a[size - 1])
    printf("Yes, the entered number is greater than those in the array\n");
  else
    printf("No, entered number is less than those in the array\n");
}