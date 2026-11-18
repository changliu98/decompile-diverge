int func0(const char *date) {
    if (strlen(date) != 10) {
        return 0;
    }

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) {
            if (date[i] != '-') {
                return 0;
            }
        } else {
            if (date[i] < '0' || date[i] > '9') {
                return 0;
            }
        }
    }

    char m_str[3];
    m_str[0] = date[0];
    m_str[1] = date[1];
    m_str[2] = '\0';

    char d_str[3];
    d_str[0] = date[3];
    d_str[1] = date[4];
    d_str[2] = '\0';

    char y_str[5];
    y_str[0] = date[6];
    y_str[1] = date[7];
    y_str[2] = date[8];
    y_str[3] = date[9];
    y_str[4] = '\0';

    int m = atoi(m_str);
    int d = atoi(d_str);
    int y = atoi(y_str);

    if (m < 1 || m > 12) {
        return 0;
    }

    if (d < 1 || d > 31) {
        return 0;
    }

    if ((m == 4 || m == 6 || m == 9 || m == 11) && d == 31) {
        return 0;
    }

    if (m == 2 && d > 29) {
        return 0;
    }

    return 1;
}