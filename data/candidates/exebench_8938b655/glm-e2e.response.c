int itos(int num, char *buf) {
    int i;
    int rem;
    int len;
    char temp;
    int is_negative = 0;

    if (num < 0) {
        num = -num;
        is_negative = 1;
        buf[0] = '-';
    } else {
        is_negative = 0;
    }

    i = is_negative - 1;
    
    // Extract digits in reverse order
    do {
        rem = num % 10;
        num = num / 10;
        i++;
        buf[i] = rem + '0';
    } while (num != 0);

    buf[i + 1] = '\0';
    len = i + 1;

    // Reverse the digits in the buffer
    while (is_negative < i) {
        temp = buf[is_negative];
        buf[is_negative] = buf[i];
        buf[i] = temp;
        is_negative++;
        i--;
    }

    return len;
}