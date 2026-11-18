int func0(int *numbers, int count) {
    // Initialize variables to store the first even and odd numbers found, defaulting to -1
    int initial_even = -1;
    int initial_odd = -1;
    
    // Iterate through the list to find the first even and first odd numbers
    for (int index = 0; index < count; index++) {
        // If the current number is even and we haven't found an even number yet, store it
        if (numbers[index] % 2 == 0 && initial_even == -1) {
            initial_even = numbers[index];
        }
        // If the current number is odd and we haven't found an odd number yet, store it
        if (numbers[index] % 2 != 0 && initial_odd == -1) {
            initial_odd = numbers[index];
        }
        // If both first even and first odd numbers have been found, exit the loop early
        if (initial_even != -1 && initial_odd != -1) break;
    }
    
    // Return the product of the first even and first odd numbers found
    return initial_even * initial_odd;
}