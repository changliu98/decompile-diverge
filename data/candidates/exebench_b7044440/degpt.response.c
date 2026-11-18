void shiftarray(int *arr)
{
  // Shift all elements one position to the left
  for (int i = 0; i < 9; i++) {
    arr[i] = arr[i + 1];
  }
  // Set the last element to -1
  arr[9] = -1;
}