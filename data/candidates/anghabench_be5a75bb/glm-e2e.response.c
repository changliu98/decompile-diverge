int frag_num(int n) {
    return (n & ~3) + 3 - (n & 3);
}