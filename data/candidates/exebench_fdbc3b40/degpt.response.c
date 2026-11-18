// Multiplies each element in the array by the given number.
// Parameters:
//   arr - pointer to the integer array
//   num - the multiplier value
void multiply_all(int *numbers, int multiplier)
{
    // Iterate through the first 10 elements of the array
    for (int index = 0; index < 10; index++) {
        // Multiply the current element by num and store the result back in the array
        numbers[index] *= multiplier;
    }
}