int func0(unsigned char c) {
    unsigned long tblidx = c & 7;
    int d;

    switch (tblidx) {
    case 0:
        d = 1;
        break;
    case 1:
        d = 3;
        break;
    case 2:
        d = 5;
        break;
    case 3:
        d = 9;
        break;
    case 4:
        d = 17;
        break;
    default:
        d = 0;
    }

    return d;
}