// Function to compute the product of all elements in arr modulo n
int func0(int *numbers, int count, int modulus)
{
  int product = 1; // Initialize product accumulator to 1
  int index;
  for (index = 0; index < count; index++) {
    // Multiply current product by (arr[i] % n), then take modulo n to prevent overflow
    product = (product * (numbers[index] % modulus)) % modulus;
  }
  // Return the final product modulo n
  return product % modulus;
}