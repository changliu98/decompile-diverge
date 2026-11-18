void util_word_to_dec(char *buf, unsigned int value) {
    int i = 0;
    char c;
    bool leading_zero = true;

    while (i < 10) {
        buf[i] = '0';
        i++;
    }
    buf[9] = '\0';

    i = 9;

    while (value > 0) {
        c = value % 10;
        value /= 10;
        buf[--i] = c + '0';
    }

    while (true) {
        if (buf[i]!= '0') {
            leading_zero = false;
        }

        if (leading_zero && i < 10) {
            i++;
        } else {
            break;
        }
    }

    while (true) {
        if (buf[i]!= '\0') {
            *buf++ = buf[i++];
        } else {
            *buf = '\0';
            break;
        }
    }
}