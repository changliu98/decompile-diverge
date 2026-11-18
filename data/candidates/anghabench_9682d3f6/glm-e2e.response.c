void bn_reverse(uint8_t *arr, int len) {
    int left = 0;
    int right = len - 1;
    
    while (left < right) {
        uint8_t temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        
        left++;
        right--;
    }
}