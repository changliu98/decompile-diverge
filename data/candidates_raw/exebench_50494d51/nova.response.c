void func0(int i, bits64 a) {
    int b;
    bits64 one;
    one = 1;
    b = i % 64;
    a[i / 64] = a[i / 64] | (one << b);
    return;
}