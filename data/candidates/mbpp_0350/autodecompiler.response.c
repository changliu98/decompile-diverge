int func0(char * s){
    int cnt[26];
    int max = 0;
    int len = strlen(s);
    memset(cnt, 0, sizeof(int) * 26);

    for (int i = 0; ; i++) {
        if (i >= len) {
            break;
        }
        cnt[s[i] - 'a']++;
    }

    for (int i = 0; ; i++) {
        if (i >= 26) {
            break;
        }
        if (cnt[i] > max) {
            max = cnt[i];
        }
    }

    return len - max;
}