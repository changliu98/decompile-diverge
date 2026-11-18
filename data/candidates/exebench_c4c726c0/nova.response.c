void check_long(long long int a, long long int b, char *c) {
    if (b - a == 8)
        *c = 'f';
    else
        *c = 't';
}