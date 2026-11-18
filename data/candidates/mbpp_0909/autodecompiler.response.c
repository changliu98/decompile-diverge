int func0(int n) {
    char str[12];
    char rev[12];
    int i, j, k, len, ans;
    for(i = n-1; ; --i) {
        if(i <= 0) {
            break;
        }
        sprintf(str, "%d", i);
        strcpy(rev, str);
        len = strlen(rev);
        for(j = 0; j < len/2; ++j) {
            char tmp = rev[j];
            rev[j] = rev[len-1-j];
            rev[len-1-j] = tmp;
        }
        if(strcmp(str, rev) == 0) {
            ans = i;
            break;
        }
    }
    return ans;
}