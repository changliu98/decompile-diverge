int* func0(int* numbers, int length) {
    int* sum = malloc(length * sizeof *numbers);

    for (int i = 0 ; ; ++i) {
        if (i >= length)
            break;

        char str[20];
        char* p = str;
        sprintf(p, "%d", abs(numbers[i]));

        int s = 0;
        int l = strlen(str);
        int j = 1;
        while (1) {
            if (j >= l)
                break;

            s += str[j] - '0';
            ++j;
        }

        if (numbers[i] > 0)
            s += str[0] - '0';
        else
            s -= str[0] - '0';

        sum[i] = s;
    }

    for (int i = 0 ; ; ++i) {
        if (i >= length)
            break;

        for (int j = 1 ; ; ++j) {
            if (j >= length)
                break;

            if (sum[j-1] > sum[j]) {
                int t = sum[j]; sum[j] = sum[j-1]; sum[j-1] = t;
                t = numbers[j]; numbers[j] = numbers[j-1]; numbers[j-1] = t;
            }
        }
    }

    free(sum);

    return numbers;
}