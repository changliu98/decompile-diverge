void SwitchToChar(char *out, unsigned char value) {
    int quotient = value / 16;
    int remainder = value % 16;

    if (quotient >= 10) {
        out[0] = (char)(quotient + 'A' - 10);
    } else {
        out[0] = (char)(quotient + '0');
    }

    if (remainder >= 10) {
        out[1] = (char)(remainder + 'A' - 10);
    } else {
        out[1] = (char)(remainder + '0');
    }
}