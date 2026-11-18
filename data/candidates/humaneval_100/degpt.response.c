int * func0(int n)
{
    // Allocate memory for an array of n integers
    int *array = malloc(n * sizeof(int));
    // Check if memory allocation was successful
    if (array) {
        // Initialize the first element with the value of n
        array[0] = n;
        // Fill the rest of the array with values incrementing by 2
        for (int i = 1; i < n; i++) {
            array[i] = array[i - 1] + 2;
        }
    }
    // Return the pointer to the allocated array
    return array;
}