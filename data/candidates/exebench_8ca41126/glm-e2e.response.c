char zhalfstr(char *s) {
    char cur = '0';
    char rem = '0';
    int i = -1;
    int started = 0;
    int leading_zeros = 0;

    while (cur != 0) {
        char next = s[i + 1];
        char half = (next - '0') >> 1;
        half += (cur & 1) * 5 + '0';

        s[i + 1 - leading_zeros] = half;

        if (half == '0' && !started) {
            leading_zeros++;
        } else {
            started = 1;
        }

        if (cur != 0) {
            rem = cur;
        }
        cur = next;
        i++;
    }

    if (i == leading_zeros) {
        s[0] = '0';
        s[1] = 0;
    } else {
        s[i - leading_zeros] = 0;
    }

    return rem;
}