bool ok_smul4(unsigned int a, unsigned int b, unsigned int *result) {
    *result = a * b;
    return *result >= a;
}