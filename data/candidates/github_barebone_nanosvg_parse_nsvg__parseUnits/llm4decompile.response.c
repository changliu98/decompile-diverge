int nsvg__parseUnits(const char* str)
{
    if (str[0] == 'p' && str[1] == 'x') return 1;
    if (str[0] == 'p' && str[1] == 't') return 2;
    if (str[0] == 'p' && str[1] == 'c') return 3;
    if (str[0] == 'm' && str[1] == 'm') return 4;
    if (str[0] == 'c' && str[1] == 'm') return 5;
    if (str[0] == 'i' && str[1] == 'n') return 6;
    if (str[0] == '%') return 7;
    if (str[0] == 'e' && str[1] == 'm') return 8;
    if (str[0] == 'e' && str[1] == 'x') return 9;
    return 0;
}