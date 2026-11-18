void itoa(unsigned short value, char *s)
{
    unsigned short index = 0;
    unsigned short index2 = 0;
    unsigned short max = 0;
    char tmp[16];

    if (value == 0) {
        s[0] = '0';
        s[1] = '\0';
        return;
    }

    while (value != 0) {
        tmp[index] = (value % 10) + '0';
        value /= 10;
        index++;
    }

    max = index;

    while (index != 0) {
        index--;
        s[index2] = tmp[index];
        index2++;
    }

    s[max] = '\0';
}