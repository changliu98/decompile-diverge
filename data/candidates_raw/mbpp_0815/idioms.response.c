void sort(int array[], int n)
{
  int low = 0;
  int mid = 0;
  int high = n - 1;
  while (mid <= high) {
    if (array[mid] == 0) {
      int temp = array[low];
      array[low] = array[mid];
      array[mid] = temp;
      low++;
      mid++;
    }
    else if (array[mid] == 1) {
      mid++;
    }
    else {
      int temp = array[mid];
      array[mid] = array[high];
      array[high] = temp;
      high--;
    }
  }
}