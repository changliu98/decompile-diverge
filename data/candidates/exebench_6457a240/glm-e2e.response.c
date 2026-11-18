void peneira(int n, int *arr) {
    int i = 1;
    int j = 2;
    int temp = arr[1];
    
    while (j <= n) {
        if (j < n && arr[j] < arr[j + 1]) {
            j++;
        }
        
        if (temp >= arr[j]) {
            break;
        }
        
        arr[i] = arr[j];
        i = j;
        j = i * 2;
    }
    
    arr[i] = temp;
}