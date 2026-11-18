int trylock(char *p) {
    char c = *p;
    if (c == '0') {
        return 1;
    }
    return 0;
}