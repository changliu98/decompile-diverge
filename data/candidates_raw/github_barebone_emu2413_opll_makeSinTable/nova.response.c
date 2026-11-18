void func0() {
    int i;
    for (i = 0; i < 256; i++)
        t[i + 256] = t[i] ^ 0x8000;
    for (i = 0; i < 512; i++)
        t[i] |= 0x8000;
    for (i = 0; i < 512; i++)
        t[i + 512] = t[i];
    for (i = 512; i < 1024; i++)
        t[i] = 0xffff;
}