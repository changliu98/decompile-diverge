void itoa(unsigned int value, char *buffer) {

    int c = sizeof (buffer) - 1;
    buffer[c] = 0;

    do {
        buffer[c--] = (value % 10) + '0';
        value = value / 10;
    } while (value);

}