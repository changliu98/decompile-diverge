bool func0(int n) {
    int digits[100];
    int temp = n;
    int count = 0;
    
    /* Extract digits (least significant first) */
    while (temp > 0) {
        digits[count] = temp % 10;
        count++;
        temp = temp / 10;
    }
    
    /* Reverse so most significant digit is at index 0 */
    int i = 0;
    int j = count - 1;
    while (i < j) {
        int t = digits[i];
        digits[i] = digits[j];
        digits[j] = t;
        i++;
        j--;
    }
    
    /* Generate Keith sequence terms until sum >= n */
    int sum = 0;
    int k = count;
    while (sum < n) {
        sum = 0;
        for (int m = 1; m <= count; m++) {
            sum += digits[k - m];
        }
        digits[k] = sum;
        k++;
    }
    
    return sum == n;
}