int func0(int *arr, int n) {
    int sum = 0;
    int i;

    // Sort the array. 
    // %rdi = arr (1st arg)
    // %rsi = n (2nd arg)
    // %edx = 4 (size of int)
    // %rcx = compare (comparator function)
    qsort(arr, n, 4, compare);

    // Initialize sum with the first element of the sorted array
    sum = arr[0];

    // Loop from i = 0 to n - 2
    for (i = 0; i < n - 1; i++) {
        // If the current element is not equal to the next element
        if (arr[i] != arr[i + 1]) {
            // Add the next element to the sum
            sum += arr[i + 1];
        }
    }

    return sum;
}