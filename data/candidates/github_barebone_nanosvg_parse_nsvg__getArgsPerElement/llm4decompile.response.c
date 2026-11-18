int nsvg__getArgsPerElement(char cmd)
{
    switch (cmd) {
        case 'M':
        case 'm':
            return 2;
        case 'L':
        case 'l':
            return 2;
        case 'H':
        case 'h':
            return 1;
        case 'V':
        case 'v':
            return 1;
        case 'C':
        case 'c':
            return 6;
        case 'S':
        case 's':
            return 4;
        case 'Q':
        case 'q':
            return 4;
        case 'T':
        case 't':
            return 2;
        case 'A':
        case 'a':
            return 7;
        case 'Z':
        case 'z':
            return 0;
        default:
            return -1;
    }
}