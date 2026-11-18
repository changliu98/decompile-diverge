__attribute__((noinline, noclone)) struct S strcpy(struct S s) {
    for (int i = 0; i < sizeof(struct S); ++i)
        s.a[i] = s.a[i];
    return s;
}