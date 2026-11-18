int func0(int *arr, int n) {
    int max_prod = 1;
    int min_prod = 1;
    int max_val = 0;
    int has_positive = 0;
    int i = 0;

    while (i < n) {
        if (arr[i] > 0) {
            max_prod = max_prod * arr[i];
            if (min_prod * arr[i] < 1) {
                min_prod = min_prod * arr[i];
            } else {
                min_prod = 1;
            }
            has_positive = 1;
        } else {
            if (arr[i] == 0) {
                max_prod = 1;
                min_prod = 1;
            } else {
                int temp = max_prod;
                if (min_prod * arr[i] > 1) {
                    max_prod = min_prod * arr[i];
                } else {
                    max_prod = 1;
                }
                min_prod = temp * arr[i];
            }
        }
        
        if (max_val < max_prod) {
            max_val = max_prod;
        }
        i++;
    }

    if (has_positive == 0 && max_val == 0) {
        return 0;
    }
    return max_val;
}