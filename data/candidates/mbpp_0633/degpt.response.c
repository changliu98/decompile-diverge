// Function to calculate the sum of XOR values of all unique pairs in the array
int func0(int *numbers, int size)
{
    int xor_sum = 0; // Initialize the result variable to store the sum of XORs
    for (int index1 = 0; index1 < size; index1++) { // Iterate through each element of the array
        for (int index2 = index1 + 1; index2 < size; index2++) { // Iterate through subsequent elements to form unique pairs
            xor_sum += numbers[index1] ^ numbers[index2]; // Compute XOR of the pair and add to the result
        }
    }
    return xor_sum; // Return the total sum of XORs of all unique pairs
}