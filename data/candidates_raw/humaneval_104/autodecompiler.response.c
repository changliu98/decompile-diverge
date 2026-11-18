void filter_numbers(int *numbers, int n, int **filtered_numbers, int *m) {
    *filtered_numbers = (int *) malloc(n * sizeof(int));
    *m = 0;

    for (int i = 0; ; i++) {
        if (i >= n) {
            break;
        }

        int number = numbers[i];
        bool has_even_digit = false;

        if (number == 0) {
            has_even_digit = true;
        }

        while (true) {
            if (number > 0 && !has_even_digit) {
                has_even_digit = true;
            }

            if (number % 2 == 0) {
                has_even_digit = true;
            }

            number /= 10;

            if (number == 0) {
                break;
            }
        }

        if (!has_even_digit) {
            (*filtered_numbers)[*m] = numbers[i];
            *m += 1;
        }
    }

    for (int i = 0; i < *m - 1; i++) {
        for (int j = 0; j < *m - i - 1; j++) {
            if ((*filtered_numbers)[j] > (*filtered_numbers)[j + 1]) {
                int tmp = (*filtered_numbers)[j];
                (*filtered_numbers)[j] = (*filtered_numbers)[j + 1];
                (*filtered_numbers)[j + 1] = tmp;
            }
        }
    }
}