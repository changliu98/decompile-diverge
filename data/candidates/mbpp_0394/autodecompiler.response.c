int func0(int *test_array, int length) {
    char is_unique = 1;
    int num_values = 0;

    int temp_array[length];

    for (int i = 0; i < length; i++) {
        int current = test_array[i];
        char found = 0;

        for (int j = 0; j < num_values; j++) {
            if (current == temp_array[j]) {
                found = 1;
                break;
            }
        }

        if (found) {
            is_unique = 0;
            break;
        } else {
            temp_array[num_values++] = current;
        }
    }

    return is_unique;
}