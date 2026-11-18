void func0(char *dest, char *src, int n) {
    if (n!= 0) {
        int i = 0;
        bool cond = (src[0]!= '\0') && (i < n - 1);
        while (cond) {
            *dest++ = *src++;
            i++;
            cond = (src[0]!= '\0') && (i < n - 1);
        }
        *dest = '\0';
    }
}