double func0(int n) {
    // Base case: if n is less than 2, return the constant value DAT_00102008
    if (n < 2) {
        return CONST_VALUE;
    }
    // Recursive case: return DAT_00102008 divided by n plus the result of func0(n-1)
    return CONST_VALUE / (double)n + func0(n - 1);
}