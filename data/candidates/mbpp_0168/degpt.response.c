// Function to count occurrences of x in array a of size n
int func0(int *array, int size, int target)
{
  int index;
  int occurrence_count = 0; // Initialize counter for occurrences
  for (index = 0; index < size; index++) {
    if (array[index] == target) { // Check if current element matches x
      occurrence_count++; // Increment count if match found
    }
  }
  return occurrence_count; // Return total count of x in the array
}