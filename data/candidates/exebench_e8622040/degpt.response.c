int doit(int *ptr, int val) {
    // Store the value pointed to by x in iVar1
    int original_val = *ptr;
    // If y is less than the original value of *x
    if (val < original_val) {
        // Update the value pointed to by x to y
        *ptr = val;
    }
    // Return 1 if y was less than the original value of *x, otherwise return 0
    return (uint)(val < original_val);
}