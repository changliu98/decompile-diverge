// Clamps the value of *a to the range [0, max) and adds the quotient to *b.
// Specifically, it performs a division by max, storing the remainder in *a
// and adding the quotient to *b.
void clamp(int *value, int *accumulator, int limit)
{
    // Add the quotient of *a divided by max to *b
    *accumulator = *value / limit + *accumulator;
    // Store the remainder of *a divided by max in *a
    *value = *value % limit;
}