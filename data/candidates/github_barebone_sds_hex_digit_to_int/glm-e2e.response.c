int hex_digit_to_int(char c) {
    int result;
    switch (c - '0') {
        case 0:  result = 0; break;  // '0'
        case 1:  result = 1; break;  // '1'
        case 2:  result = 2; break;  // '2'
        case 3:  result = 3; break;  // '3'
        case 4:  result = 4; break;  // '4'
        case 5:  result = 5; break;  // '5'
        case 6:  result = 6; break;  // '6'
        case 7:  result = 7; break;  // '7'
        case 8:  result = 8; break;  // '8'
        case 9:  result = 9; break;  // '9'
        case 17: result = 10; break; // 'A'
        case 18: result = 11; break; // 'B'
        case 19: result = 12; break; // 'C'
        case 20: result = 13; break; // 'D'
        case 21: result = 14; break; // 'E'
        case 22: result = 15; break; // 'F'
        case 49: result = 10; break; // 'a'
        case 50: result = 11; break; // 'b'
        case 51: result = 12; break; // 'c'
        case 52: result = 13; break; // 'd'
        case 53: result = 14; break; // 'e'
        case 54: result = 15; break; // 'f'
        default: result = 0; break;
    }
    return result;
}