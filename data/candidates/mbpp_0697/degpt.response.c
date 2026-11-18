// Function to count the number of even integers in an array
int func0(int *numbers, int length)
{
  int even_count = 0; // Initialize counter for even numbers
  for (int index = 0; index < length; index++) { // Iterate through each element in the array
    if (numbers[index] % 2 == 0) { // Check if the current element is even
      even_count++; // Increment the counter if the element is even
    }
  }
  return even_count; // Return the total count of even numbers
}