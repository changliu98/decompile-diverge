int max(int arr[], int len) {
    int temp;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (arr[i] > arr[j]) {
                temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }

    int res;
    for (int i = len - 1; i >= 0; i--) {
        if (is_palindrome(arr[i]) % 2 != 0) {
            res = arr[i];
            break;
        }
    }
    return res;
}