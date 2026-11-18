int func0(int *arr, int n) {
    int i = 0;
    int count;
    int j;
    int result;

    while (i < n) {
        count = 0;
        j = 0;
        while (j < n) {
            if (arr[i] == arr[j]) {
                count++;
            }
            j++;
        }
        
        if (count % 2 != 0) {
            result = arr[i];
            return result;
        }
        
        i++;
    }
    
    result = -1;
    return result;
}