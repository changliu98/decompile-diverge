int Fibonacci_search(int arr[], int n, int x) {
    int fib[20] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181};
    int low = 1;
    int high = n;
    int k = 0;
    
    // Find the smallest Fibonacci number greater than or equal to n
    while (n > fib[k] - 1) {
        k++;
    }
    
    // Extend the array to the size of fib[k] - 1 by padding with the last element
    int temp_high = n;
    while (temp_high < fib[k] - 1) {
        arr[temp_high] = arr[n];
        temp_high++;
    }
    
    // Main Fibonacci search loop
    while (low <= high) {
        int mid = low + fib[k - 1] - 1;
        
        if (x < arr[mid]) {
            high = mid - 1;
            k = k - 1;
        } else if (x > arr[mid]) {
            low = mid + 1;
            k = k - 2;
        } else {
            // Element found
            if (mid <= n) {
                return mid;
            } else {
                return n; // It's one of the padded duplicates
            }
        }
    }
    
    return 0; // Element not found
}