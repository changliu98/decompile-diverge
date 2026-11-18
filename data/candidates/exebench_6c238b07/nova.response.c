int genx(char *s, char *t) {
    int i, j, k, c;
    short int map[256];

    for (i = 0; i < 256; i++)
        map[i] = -1;

    for (i = 0; i < 256; i++) {
        while (i < 256) {
            c = t[i];
            j = map[c];
            if (j!= -1) {
                k = 1;
                break;
            }
            map[c] = i;
        }
    }

    for (i = 0; i < 256; i++) {
        s[i] = map[i];
    }

    return (k == 0)? -1 : 0;
}