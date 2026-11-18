int func0(int *arr1, int *arr2, int n) {
    // Sort both arrays
    qsort(arr1, n, 4, compare);
    qsort(arr2, n, 4, compare);

    int balance = 1;
    int max_balance = 1;
    int i = 1;
    int j = 0;

    // Traverse arrays to find the maximum balance
    while (i < n && j < n) {
        if (arr1[i] > arr2[j]) {
            balance--;
            j++;
        } else {
            balance++;
            i++;
            if (balance > max_balance) {
                max_balance = balance;
            }
        }
    }

    return max_balance;
}