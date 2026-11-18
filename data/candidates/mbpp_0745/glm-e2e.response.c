void func0(int start, int end, int *arr, int *count) {
    *count = 0;
    for (int i = start; i <= end; i++) {
        int is_self_dividing = 1;
        int temp = i;
        
        while (temp > 0) {
            int digit = temp % 10;
            if (digit == 0 || i % digit != 0) {
                is_self_dividing = 0;
                break;
            }
            temp /= 10;
        }
        
        if (is_self_dividing) {
            arr[*count] = i;
            (*count)++;
        }
    }
}