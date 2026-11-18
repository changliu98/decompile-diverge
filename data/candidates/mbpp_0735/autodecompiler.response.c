int func0(int n) {
    int flipped;

    if (n == 1) {
        flipped = 1;
    } else {
        int original = n;
        flipped = original ^ set_middle_bits(n);
    }

    return flipped;
}