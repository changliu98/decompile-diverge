int nsvg__parseUnits(const char* str) {
    if (str[0] == 'p' && str[1] == 'x') {
        return 1;
    } else if (str[0] == 'p' && str[1] == 't') {
        return 2;
    } else if (str[0] == 'p' && str[1] == 'c') {
        return 3;
    } else if (str[0] == 'm' && str[1] == 'm') {
        return 4;
    } else if (str[0] == 'c' && str[1] == 'm') {
        return 5;
    } else if (str[0] == 'i' && str[1] == 'n') {
        return 6;
    } else if (str[0] == '%') {
        return 7;
    } else if (str[0] == 'e' && str[1] == 'm') {
        return 8;
    } else if (str[0] == 'e' && str[1] == 'x') {
        return 9;
    } else {
        return 0;
    }
}