char * func0(int *numbers,int count)
{
  // Initialize index i to 1 to start checking from the second element
  int index = 1;
  // Loop while i is less than n and the current element equals the first element
  while (count > index && numbers[index] == *numbers) {
    // Increment index to check the next element
    index++;
  }
  // Return "YES" if all elements from index 1 to n-1 are equal to the first element, otherwise return "NO"
  return count <= index ? "YES" : "NO";
}