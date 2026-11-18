// Reverses the first 10 elements of the integer array pointed to by p
void reverseInt(int *array)
{
    // Iterate through the first half of the 10-element array
    for (int index = 0; index < 5; index++) {
        // Store the current element in a temporary variable
        int tempValue = array[index];
        // Swap the current element with its counterpart from the end
        array[index] = array[9 - index];
        // Assign the stored value to the counterpart position
        array[9 - index] = tempValue;
    }
}