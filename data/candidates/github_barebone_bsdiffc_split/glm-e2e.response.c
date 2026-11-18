void split(int64_t *arr1, int64_t *arr2, int64_t start, int64_t length, int64_t offset) {
    if (length < 16) {
        for (int64_t i = start; i < start + length; ) {
            int64_t count = 1;
            int64_t pivot = arr2[arr1[i] + offset];
            
            for (int64_t j = i + 1; j < start + length; j++) {
                if (arr2[arr1[j] + offset] < pivot) {
                    pivot = arr2[arr1[j] + offset];
                    count = 0;
                }
                if (arr2[arr1[j] + offset] == pivot) {
                    int64_t temp = arr1[i + count];
                    arr1[i + count] = arr1[j];
                    arr1[j] = temp;
                    count++;
                }
            }
            
            for (int64_t k = 0; k < count; k++) {
                arr2[arr1[i + k]] = i + count - 1;
            }
            
            if (count == 1) {
                arr1[i] = -1;
            }
            
            i += count;
        }
    } else {
        int64_t mid = start + length / 2;
        int64_t pivot = arr2[arr1[mid] + offset];
        
        int64_t left_count = 0;
        int64_t right_count = 0;
        
        for (int64_t i = start; i < start + length; i++) {
            if (arr2[arr1[i] + offset] < pivot) {
                left_count++;
            }
            if (arr2[arr1[i] + offset] == pivot) {
                right_count++;
            }
        }
        
        left_count += start;
        right_count += left_count;
        
        int64_t i = start;
        int64_t j = 0;
        int64_t k = 0;
        
        for (; i < left_count; i++) {
            if (arr2[arr1[i] + offset] < pivot) {
                i++;
            } else if (arr2[arr1[i] + offset] == pivot) {
                int64_t temp = arr1[i];
                arr1[i] = arr1[left_count + j];
                arr1[left_count + j] = temp;
                j++;
            } else {
                int64_t temp = arr1[i];
                arr1[i] = arr1[right_count + k];
                arr1[right_count + k] = temp;
                k++;
            }
        }
        
        for (; left_count + j < right_count; ) {
            if (arr2[arr1[left_count + j] + offset] == pivot) {
                j++;
            } else {
                int64_t temp = arr1[left_count + j];
                arr1[left_count + j] = arr1[right_count + k];
                arr1[right_count + k] = temp;
                k++;
            }
        }
        
        if (left_count > start) {
            split(arr1, arr2, start, left_count - start, offset);
        }
        
        for (int64_t l = 0; l < right_count - left_count; l++) {
            arr2[arr1[left_count + l]] = right_count - 1;
        }
        
        if (left_count == right_count - 1) {
            arr1[left_count] = -1;
        }
        
        if (start + length > right_count) {
            split(arr1, arr2, right_count, start + length - right_count, offset);
        }
    }
}