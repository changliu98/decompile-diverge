char* string_to_slong(char* str, long* out_val) {
    int is_neg;
    char c = *str;

    if (c == '-') {
        is_neg = 1;
        str++;
        c = *str;
    } else if (c == '+') {
        is_neg = 0;
        str++;
        c = *str;
    } else {
        is_neg = 0;
    }

    *out_val = 0;

    // Loop while the character is a digit ('0' to '9')
    // (unsigned)(c - '0') <= 9 is equivalent to the assembly's sub $0x30, %eax; cmp $0x9, %eax; ja
    while ((unsigned int)(c - '0') <= 9) {
        *out_val = (*out_val * 10) + (c - '0');
        str++;
        c = *str;
    }

    if (is_neg) {
        *out_val = -*out_val;
    }

    return str;
}