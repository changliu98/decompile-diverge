void func0(signed char *c, char *v) {
    for (; *v!= '\0'; v++)
        if ('0' <= *v && *v <= '7')
            *c &= (~(*v - '0') ^ 0xff);
}