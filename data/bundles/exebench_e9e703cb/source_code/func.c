#include <stdio.h>

#include <limits.h>

#include <assert.h>

#include <string.h>

char *int2str(int val, char *str, int base) {
    static char tab[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char buf[sizeof(int) * 8 + 1] = "";
    char *p = buf;
    char *p2 = str;
    unsigned uval = val;


    if (base < 2 || base > 36) {
        *str = '\0';
        return str;
    }


    uval = val;
    if (val < 0 && base == 10) {
        uval = -val;
    }

    do {
        *p++ = tab[uval % base];

    } while (uval /= base);

    if (val < 0 && base == 10) {
        *p++ = '-';
    }

    p--;
    while (p >= buf && (*p2++ = *p) != '\0')
        p--;
    *p2 = '\0';

    return str;
}
