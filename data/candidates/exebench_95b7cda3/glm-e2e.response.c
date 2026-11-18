char* itoa(char* str, int base, long long value) {
    char* ptr = str;
    long long original_value = value;
    int radix = 10;

    if (base == 100) {
        if (value < 0) {
            *ptr++ = '-';
            str++;
            original_value = -value;
        }
    } else if (base == 120) {
        radix = 16;
    }

    do {
        int remainder = original_value % radix;
        char c = (remainder < 10 ? '0' : 'a' - 10) + remainder;
        *ptr++ = c;
        original_value /= radix;
    } while (original_value != 0);

    *ptr = '\0';

    char* start = str;
    char* end = ptr - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }

    return str;
}