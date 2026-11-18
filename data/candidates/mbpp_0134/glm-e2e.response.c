const char* func0(int* arr, int n, int flag) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum += arr[i];
        i++;
    }
    
    const char* result;
    if (flag == 1) {
        if (sum % 2 == 0) {
            result = "even";
        } else {
            result = "odd";
        }
    } else {
        result = "odd";
    }
    return result;
}