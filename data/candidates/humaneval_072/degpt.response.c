// Checks if the array is a palindrome and if the sum of its elements is less than or equal to w.
_Bool func0(int *arr, int n, int limit)
{
    int totalSum = 0;
    int index = 0;
    // Iterate through the first half of the array to check for palindrome property
    while (n / 2 > index) {
        // If elements at symmetric positions are not equal, it's not a palindrome
        if (arr[index] != arr[n - 1 - index]) return false;
        // Add the sum of symmetric elements
        totalSum += arr[index] + arr[n - 1 - index];
        index++;
    }
    // If the array size is odd, add the middle element to the sum
    if (n % 2 == 1) {
        totalSum += arr[n / 2];
    }
    // Return true if the total sum is less than or equal to w
    return totalSum <= limit;
}