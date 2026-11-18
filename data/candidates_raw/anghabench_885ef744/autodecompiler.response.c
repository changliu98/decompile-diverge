void ultoa(unsigned long num, unsigned int base, bool uppercase, char *bf) {
    int n = 0;
    unsigned int d = 1;
    while (true) {
        if (num / d >= base) {
            d *= base;
        } else {
            break;
        }
    }
    while (true) {
        if (d != 0) {
            int x = num / d;
            num %= d;
            d /= base;
            if ((n != 0) || (x > 0)) {
                int c = x + '0';
                if (uppercase) {
                    c += 'A' - '0' - 10;
                } else {
                    c += 'a' - '0' - 10;
                }
                *bf++ = c;
                ++n;
            }
        } else {
            *bf = '\0';
            return;
        }
    }
}