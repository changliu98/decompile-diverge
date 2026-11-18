int func0(char *s, int *a) {
    int i = 0;
    int j = 0;
    int k;
    int l;
    int m;
    int n;
    int o;
    int p;
    int q;
    int r;
    int t;
    int u;
    int v;
    int w;
    int x;
    int y;
    int z;
    char c;
    char d;
    char e;
    char f;
    char g;
    char h;
    char i1;
    char j1;
    char k1;
    char l1;
    char m1;
    char n1;
    char o1;
    char p1;
    char q1;
    char r1;
    char s1;
    char t1;
    char u1;
    char v1;
    char w1;
    char x1;
    char y1;
    char z1;
    while (1) {
        if (j < 5) {
            a[j] = 0;
            j++;
        } else
            break;
    }
    while (1) {
        c = *s++;
        if (c == 0)
            break;
        if (c >= '0' && c <= '9')
            d = c - '0';
        else if (c >= 'a' && c <= 'f')
            d = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F')
            d = c - 'A' + 10;
        else if (strchr("+-*/%=()<>,;:!?&|^$#@`~", c)!= 0)
            continue;
        else
            break;
        while (1) {
            if (i < 32) {
                a[i / 8] = a[i / 8] * 16 + d;
                i++;
            } else
                break;
        }
    }
    if (i == 32)
        return 1;