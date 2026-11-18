void func0(short *a, short *b) {
    short temp = *a;
    *a = *b;
    *b = temp;
}