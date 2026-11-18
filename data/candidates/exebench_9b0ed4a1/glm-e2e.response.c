float binary_search(const float *arr, int size, float target) {
    float result;

    // Check if the array is empty
    if (size <= 0) {
        return NAN;
    }

    // Check the first element
    if (arr[0] == target) {
        return 0.0f;
    }
    
    // If target is smaller than the first element, return NaN
    if (arr[0] > target) {
        return NAN;
    }

    // Check the last element
    if (arr[size - 1] < target) {
        return NAN;
    }
    
    if (arr[size - 1] == target) {
        return (float)(size - 1);
    }

    // Standard binary search
    int low = 0;
    int high = size - 1;
    
    while (low <= high) {
        int mid = low + (high - low) / 2; // or simply (low + high) / 2
        
        if (arr[mid] > target) {
            high = mid - 1;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            return (float)mid;
        }
    }

    // If exact match is not found, perform linear interpolation
    // At this point, 'low' is the upper bound and 'high' is the lower bound
    float fraction = (target - arr[high]) / (arr[low] - arr[high]);
    result = (float)((double)high * (1.0 - (double)fraction) + (double)low * (double)fraction);
    
    return result;
}