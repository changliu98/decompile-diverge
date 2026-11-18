int stbhw__change_color(int a, int b, int *p) {
    int i, j, k, l;
    if (p!= NULL) {
        for (i = 0, j = 0;; j++) {
            if (j < b) {
                if (j!= a)
                    i += p[j];
            } else
                break;
        }
        k = rand() % (i >> 4);
        for (i = 0, j = 0;; j++) {
            if (j < b) {
                if (j!= a) {
                    i += p[j];
                    if (i > k)
                        break;
                }
            } else
                break;
        }
    }
    assert(j < b);
    return j;
}