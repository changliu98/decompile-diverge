int arraylist_sort_internal(void **arr, unsigned int size, int (*cmp)(const void *, const void *)) {
    if (size > 1) {
        void *pivot = arr[size - 1];
        unsigned int i = 0;
        
        for (unsigned int j = 0; j < size - 1; j++) {
            if (cmp(arr[j], pivot) < 0) {
                void *temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
                i++;
            }
        }
        
        unsigned int right_size = size - i - 1;
        arr[size - 1] = arr[i];
        arr[i] = pivot;
        
        arraylist_sort_internal(arr, i, cmp);
        arraylist_sort_internal(arr + i + 1, right_size, cmp);
    }
    
    return 0; // Assuming an int return type based on standard calling conventions, though void is possible.
}