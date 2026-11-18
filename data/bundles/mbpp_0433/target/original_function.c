void func0(int arr[], int size, int number) {
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
  if (number > arr[size - 1]) {
    printf("Yes, the entered number is greater than those in the array\n");
  } else {
    printf("No, entered number is less than those in the array\n");
  }
}