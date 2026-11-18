void foo(struct S *s, int b, int c) {
    int a = s->a;
    int d = s->b;
    
    for (int i = 0; i < 1; i++) {
        int e = 0;
        if (b != 0) e |= 1;
        if (d != 0) e |= 2;
        if (c != 0) e |= 1;
        if (a != 0) e |= 2;
        if ((1 >> i) != 0) e |= 1;
        
        s->c[i + 2] = e;
    }
}