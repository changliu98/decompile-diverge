int validateRegexSyntax(char *s) {
    int i = 0;
    char c;
    char f = 0;
    char a = 0;
    char b = 0;
    char d = 0;
    char e = 0;
    char g = 0;
    char h = 0;
    char j = 0;
    char k = 0;
    char l = 0;
    char m = 0;
    char n = 0;
    char o = 0;
    char p = 0;
    char q = 0;
    char r = 0;
    char t = 0;
    char u = 0;
    char v = 0;
    char w = 0;
    char x = 0;
    char y = 0;
    char z = 0;
    for (i = 0;; i++) {
        c = s[i];
        if (c == 0)
            break;
        if (i % 2 == 0) {
            if (c == '[') {
                a = 1;
                b = 0;
                d = 0;
                e = 0;
            }
            if (c == ']') {
                a = 0;
                b = 1;
                d = 0;
                e = 0;
            }
            if (c == '(') {
                g = 1;
                h = 0;
                j = 0;
                k = 0;
            }
            if (c == ')') {
                g = 0;
                h = 1;
                j = 0;
                k = 0;
            }
            if (c == '{') {
                l = 1;
                m = 0;
                n = 0;
                o = 0;
            }
            if (c == '}') {
                l = 0;
                m = 1;
                n = 0;
                o = 0;
            }
        }
        if (i % 2 == 1) {
            if (c == '*') {
                p = 0;
                q = 1;
                r = 0;
                t = 0;
            }
            if (c == '+') {
                p = 0;
                q = 0;
                r = 1;
                t = 0;
            }
            if (c == '?') {
                p = 1;
                q = 0;
                r = 0;
                t = 0;
            }
            if (c == '^') {
                p = 0;
                q = 0;
                r = 0;
                t = 1;
            }
        }
    }
    if (a == 0 && b == 0 && d == 0 && e == 0 && g == 0 && h == 0 && j == 0 &&
        k == 0 && l == 0 && m == 0 && n == 0 && o == 0 && p == 0 && q == 0 &&
        r == 0 && t == 0 && u == 0 && v == 0 && w == 0 && x == 0 && y == 0 &&
        z == 0)
        return 1;
    else
        return 0;
}