void func0(int arr[], int n) {
  int out_of_place = -1;
  for (int index = 0; index < n; ++index) {
    if (out_of_place >= 0) {
      if ((arr[index] >= 0 && arr[out_of_place] < 0) ||
          (arr[index] < 0 && arr[out_of_place] >= 0)) {
        right_rotate(arr, n, out_of_place, index);
        if (index - out_of_place > 2) {
          out_of_place += 2;
        } else {
          out_of_place = -1;
        }
      }
    }
    if (out_of_place == -1) {
      if ((arr[index] >= 0 && index % 2 == 0) ||
          (arr[index] < 0 && index % 2 == 1)) {
        out_of_place = index;
      }
    }
  }
}