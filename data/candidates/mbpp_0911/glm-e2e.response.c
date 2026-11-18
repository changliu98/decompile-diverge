int func0(int *arr, int n) {
    if (n < 3) {
        return -1;
    }

    // Bubble sort the array
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] < arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    // Extract the 3 largest and 2 smallest elements
    int max1 = arr[0];
    int max2 = arr[1];
    int max3 = arr[2];
    int min1 = arr[n - 1];
    int min2 = arr[n - 2];

    // Calculate the two possible maximum products of 3 elements
    int prod1 = max1 * max2 * max3;
    int prod2 = max1 * min1 * min2;

    // Return the maximum of the two products
    if (prod1 > prod2) {
        return prod1;
    } else {
        return prod2;
    }
}