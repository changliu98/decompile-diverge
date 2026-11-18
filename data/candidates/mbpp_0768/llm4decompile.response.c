int func0(int x) {
    int parity = 0;
    while (x != 0) {
        parity += 1;
        x &= x - 1;
    }
    return (parity % 2) == 1;
}