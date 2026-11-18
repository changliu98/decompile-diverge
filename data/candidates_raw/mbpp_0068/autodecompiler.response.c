int check_strict_monotonicity(int *data_array, int num_values) {
    char increasing = 1, decreasing = 1;
    int i;
    for (i = 0; ; i++) {
        if (i >= num_values - 1)
            break;
        if (data_array[i] > data_array[i + 1])
            increasing = 0;
        if (data_array[i] < data_array[i + 1])
            decreasing = 0;
    }
    return (increasing || decreasing);
}