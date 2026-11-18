void func0(int a, int b, int *c, int *d) {
    *d = 0;
    
    if (b < a) {
        int temp = a;
        a = b;
        b = temp;
    }
    
    for (int i = a; i <= b; i++) {
        if (i < 10 && i % 2 == 0) {
            int index = *d;
            *d = index + 1;
            c[index] = i;
        }
    }
}