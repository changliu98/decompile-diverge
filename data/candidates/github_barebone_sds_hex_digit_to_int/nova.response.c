int hex_digit_to_int(char c) {
    long i, j;
    long x = c;
    int y;
    switch (x) {
    case '0':
        y = 0;
        break;
    case '1':
        y = 1;
        break;
    case '2':
        y = 2;
        break;
    case '3':
        y = 3;
        break;
    case '4':
        y = 4;
        break;
    case '5':
        y = 5;
        break;
    case '6':
        y = 6;
        break;
    case '7':
        y = 7;
        break;
    case '8':
        y = 8;
        break;
    case '9':
        y = 9;
        break;
    case 'a':
    case 'A':
        y = 10;
        break;
    case 'b':
    case 'B':
        y = 11;
        break;
    case 'c':
    case 'C':
        y = 12;
        break;
    case 'd':
    case 'D':
        y = 13;
        break;
    case 'e':
    case 'E':
        y = 14;
        break;
    case 'f':
    case 'F':
        y = 15;
        break;
    default:
        y = 0;
    }
    return y;
}