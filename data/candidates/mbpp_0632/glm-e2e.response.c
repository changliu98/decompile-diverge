void func0(int *arr1, int n, int *arr2) {
    int zero_count = 0;
    int j = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr1[i] == 0) {
            zero_count++;
        } else {
            arr2[j++] = arr1[i];
        }
    }
    
    for (int i = 0; i < zero_count; i++) {
        arr2[j++] = 0;
    }
}