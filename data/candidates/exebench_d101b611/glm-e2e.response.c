int and_peep2_q(int a, int* b) {
    *b = a & 0xfe;
    return a;
}