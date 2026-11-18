// Sorts two integers pointed to by p0 and p1 in ascending order
void _Sort(int *firstPtr, int *secondPtr)
{
  // If the value at p1 is less than the value at p0, swap them
  if (*secondPtr < *firstPtr) {
    int tempValue = *firstPtr; // Store the value of *p0 in a temporary variable
    *firstPtr = *secondPtr;      // Assign the value of *p1 to *p0
    *secondPtr = tempValue;     // Assign the stored value (original *p0) to *p1
  }
}