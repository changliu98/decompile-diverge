void itoa(int value, char *str) {
    char *start = str;
    char *end;
    int i;
    char temp;

    if (value < 0) {
        i = -value;
        *start = '-';
        start++;
    } else {
        i = value;
    }

    end = start;
    do {
        *end = (i % 10) + '0';
        i /= 10;
        end++;
    } while (i != 0);

    *end = '\0';
    end--;

    while (start < end) {
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}