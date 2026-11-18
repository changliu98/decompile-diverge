int* __cdecl func0(int* nums, int size) {
    if (nums == NULL || size <= 0) {
        return nums;
    }

    int* digit_sums = (int*)malloc(sizeof(int) * size);
    if (digit_sums == NULL) {
        return nums;
    }

    // Calculate the sum of digits for each number
    for (int i = 0; i < size; ++i) {
        unsigned int abs_num = abs(nums[i]);
        char w[12]; // 32-bit integers max length is 11 characters (including '-' and '\0')
        sprintf(w, "%u", abs_num);
        
        int length = strlen(w);
        int current_sum = 0;
        
        // The first digit determines the sign behavior
        int first_digit = w[0] - '0';
        
        if (nums[i] <= 0) {
            current_sum -= first_digit;
        } else {
            current_sum += first_digit;
        }
        
        // Sum the remaining digits
        for (int j = 1; j < length; ++j) {
            current_sum += w[j] - '0';
        }
        
        digit_sums[i] = current_sum;
    }

    // Bubble sort the original array based on the computed digit sums
    for (int i = 0; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            if (digit_sums[j - 1] > digit_sums[j]) {
                // Swap digit sums
                int temp_sum = digit_sums[j];
                digit_sums[j] = digit_sums[j - 1];
                digit_sums[j - 1] = temp_sum;
                
                // Swap original numbers
                int temp_num = nums[j];
                nums[j] = nums[j - 1];
                nums[j - 1] = temp_num;
            }
        }
    }

    free(digit_sums);
    return nums;
}