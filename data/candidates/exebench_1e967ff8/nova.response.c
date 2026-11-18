void right_shift_str(char *str, int n) {
    int i = 0;
    char *p = str;
    while (*p!= '\0') {
        if (*p!= i) {
            i++;
            p++;
        } else {
            int j = 0;
            while (j < n) {
                char tmp = *(p + i - 1);
                int k = i - 1;
                while (k > 0) {
                    *(p + k) = *(p + k - 1);
                    k--;
                }
                *p = tmp;
                j++;
            }
        }
    }
}