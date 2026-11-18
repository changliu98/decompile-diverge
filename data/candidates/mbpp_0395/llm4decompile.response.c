char func0(char *str1)
{
    int ctr[256];
    char char_order[256];
    int idx = 0;
    int length = strlen(str1);
    int i;
    memset(ctr, 0, sizeof(ctr));
    for (i = 0; i < length; i++) {
        char ch = str1[i];
        if (ctr[ch] == 0) {
            char_order[idx] = ch;
            idx++;
        }
        ctr[ch]++;
    }
    for (i = 0; i < idx; i++) {
        if (ctr[char_order[i]] == 1) {
            return char_order[i];
        }
    }
    return 0;
}