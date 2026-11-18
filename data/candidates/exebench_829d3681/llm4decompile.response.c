void word2string(unsigned int word, char *buffer)
{
    static const unsigned int _smth[] = {10000, 1000, 100, 10, 1};
    char *p = buffer;
    int i;

    if (word == 0) {
        buffer[0] = '0';
        buffer[1] = ' ';
        buffer[2] = 0;
        buffer[3] = 0;
        return;
    }

    for (i = 0; i < 5; i++) {
        unsigned int d = word / _smth[i];
        if (p != buffer || d != 0) {
            *p++ = '0' + d;
            word %= _smth[i];
        }
    }
    *p++ = ' ';
    *p++ = 0;
}