int func0(int *arr, int n) {
    int count = 0;
    int i = 0;
    
    while (i < n) {
        if (arr[i] == -1) {
            break;
        }
        count++;
        i++;
    }
    
    return count;
}