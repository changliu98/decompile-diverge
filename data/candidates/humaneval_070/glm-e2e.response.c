void func0(int *arr1, int n, int *arr2) {
    int i, j, temp;
    int left = 0;
    int right = n - 1;
    int k = 0;

    // Bubble sort the input array in ascending order
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (arr1[i] > arr1[j]) {
                temp = arr1[i];
                arr1[i] = arr1[j];
                arr1[j] = temp;
            }
        }
    }

    // Rearrange the sorted array into arr2 in a wave-like form:
    // picking elements from the left and right ends alternately.
    while (left <= right) {
        if (left == right) {
            arr2[k++] = arr1[left++];
        } else {
            arr2[k++] = arr1[left++];
            arr2[k++] = arr1[right--];
        }
    }
}