int nsvg__getArgsPerElement(char c) {
    switch (c) {
        case 'A':
        case 'a':
            return 7;
        case 'C':
        case 'c':
            return 6;
        case 'H':
        case 'h':
            return 1;
        case 'L':
        case 'l':
        case 'M':
        case 'm':
        case 'T':
        case 't':
            return 2;
        case 'Q':
        case 'q':
        case 'S':
        case 's':
            return 4;
        case 'V':
        case 'v':
            return 1;
        case 'Z':
        case 'z':
            return 0;
        default:
            return -1;
    }
}