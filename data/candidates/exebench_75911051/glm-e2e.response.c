int divide(int a, int b, int *remainder) {
    int quotient = a / b;
    *remainder = a % b;
    return quotient;
}