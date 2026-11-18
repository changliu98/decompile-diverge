int func0(int *arr, int n) {
    int *filtered = (int *)alloca(n * sizeof(int));
    int count = 0;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] > 0) {
            filtered[count++] = arr[i];
        }
    }
    
    qsort(filtered, count, sizeof(int), compare);
    
    int sum = 0;
    for (int i = 0; i < 3 && i < count; i++) {
        sum += filtered[i];
    }
    
    return sum;
}