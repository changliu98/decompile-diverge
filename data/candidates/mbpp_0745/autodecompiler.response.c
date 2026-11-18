void func0(int start, int end, int divisors[], int *size) {
    int i, j, digit, num;
    bool divisible;

    *size = 0;

    for (i = start; i <= end; ++i) {
        divisible = true;
        num = i;

        while (num > 0) {
            digit = num % 10;

            if (!digit || i % digit) {
                divisible = false;
                break;
            }

            num /= 10;
        }

        if (divisible) {
            divisors[*size] = i;
            (*size)++;
        }
    }
}