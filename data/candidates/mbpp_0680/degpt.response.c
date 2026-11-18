// Returns true if the array 'nums' of length 'size' is sorted in non-decreasing order.
// Iterates through the array to find the first index where the order is violated.
_Bool isSorted(int *array,int length)
{
  int index = 0;
  // Advance 'i' while the next element is greater than or equal to the current element.
  // This loop finds the first position where nums[i] > nums[i+1], if any.
  while (index < length - 1 && array[index + 1] >= array[index]) {
    index++;
  }
  // If 'i' reached the last index, the entire array was sorted.
  return index == length - 1;
}