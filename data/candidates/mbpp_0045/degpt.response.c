int func0(int *arr, int n)
{
    int idx;
    int result;
    
    // Initialize gcd with the GCD of the first two elements
    result = find_gcd(*arr, arr[1]);
    
    // Iteratively compute the GCD of the current result with each subsequent element
    for (idx = 2; idx < n; idx = idx + 1) {
        result = find_gcd(result, arr[idx]);
    }
    
    // Return the GCD of all elements in the array
    return result;
}