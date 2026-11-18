void reorder(int *first, int *second)
{
  // If the value pointed to by b is less than the value pointed to by a,
  // swap the values so that *a <= *b
  if (*second < *first) {
    int temp = *first;  // Store the value of *a in a temporary variable
    *first = *second;     // Assign the value of *b to *a
    *second = temp;      // Assign the original value of *a (stored in t) to *b
  }
}