int cal_intervals(int* arr, int* intervals, int size) {
    int count = 0;
    int i = 0;
    int length;

    // Skip leading zeros
    while (i < size && arr[i] == 0) {
        i++;
    }

    while (i < size) {
        // Skip non-zeros
        while (i < size && arr[i] != 0) {
            i++;
        }

        length = 0;
        // Count zeros
        while (i < size && arr[i] == 0) {
            i++;
            length++;
        }

        if (i < size) {
            intervals[count] = length;
            count++;
        }
    }

    return count + 1;
}