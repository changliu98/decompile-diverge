void h(int *ptr, int val)
{
    // If y is less than the value pointed to by x, recursively call h with the current value of *x
    if (val < *ptr) {
        h(ptr, *ptr);
    }
    // Otherwise, subtract y from the value pointed to by x
    else {
        *ptr = *ptr - val;
    }
}