void word2string(unsigned int number, char *to) {
    char *tmp = to;
    if (!number) {
        strcpy__bench(to, "0 ");
        return;
    }
    int i;
    for (i = 0; i < 6; i++) {
        if (i == 6 - 1) {
            strcpy__bench(tmp, " ");
            break;
        }
        if (tmp == to + number / word2string__smth[i]) {
            continue;
        }
        *tmp = '0' + number / word2string__smth[i];
        tmp++;
        number %= word2string__smth[i];
    }
}