static void func0(int *pX, int *pY, int *pZ, int *pW) {
    int a, d;
    asm volatile("cpuid"
                 : "=a"(a), "=d"(d)
                 : "0"(1), "c"(*pW)
                 :);
    if (pX)
        *pX = ((d >> 26) & 1);
    if (pY)
        *pY = (d & 1);
}