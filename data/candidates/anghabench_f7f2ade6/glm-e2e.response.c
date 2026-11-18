int pmc_overflow(int val) {
    if (val < 0) {
        return 1;
    } else {
        return 0;
    }
}