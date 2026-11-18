int computesizes(int *arr, int *target) {
    int sum = 0;
    int best_sum = 0;
    int best_size = 0;
    int i = 0;
    int size = 1;

    while (size / 2 < *target) {
        if (arr[i] > 0) {
            sum += arr[i];
            if (sum > size / 2) {
                best_size = size;
                best_sum = sum;
            }
        }
        
        if (sum == *target) {
            break;
        }
        
        i++;
        size *= 2;
    }

    *target = best_size;
    return best_sum;
}