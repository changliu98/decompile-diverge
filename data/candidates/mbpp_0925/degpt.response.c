// Function to calculate the product of all elements in the array
int func0(int *numbers, int length)
{
  int result = 1; // Initialize product to 1
  for (int index = 0; index < length; index++) {
    result = numbers[index] * result; // Multiply current element with product
  }
  return result; // Return the final product
}