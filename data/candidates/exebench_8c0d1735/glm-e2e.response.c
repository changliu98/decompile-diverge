int and_peep2_qi(int a, int *b) {
    *b = a & 0x5f;
    return a;
}