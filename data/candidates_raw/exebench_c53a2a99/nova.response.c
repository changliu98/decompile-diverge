void func0(char *s) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int m = 0;
    int n = 0;
    int o = 0;
    int p = 0;
    int q = 0;
    int r = 0;
    int t = 0;
    int u = 0;
    int v = 0;
    int w = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    char *a;
    a = "0123456789abcdefghijklmnopqrstuvwxyz";
    while (1) {
        if (s[i]!= 0) {
            s[i] = s[i] - a[j];
            if (i == 3) {
                i = 0;
            } else {
                i++;
            }
        } else {
            break;
        }
    }
}