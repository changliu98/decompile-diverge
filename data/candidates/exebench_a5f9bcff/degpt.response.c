int foo(int *first_value, int *second_value)
{
    // Increment the value pointed to by p1 by 1
    *first_value += 1;
    // Increment the value pointed to by p2 by 1
    *second_value += 1;
    // Return the sum of the incremented values minus 2
    return *first_value + *second_value - 2;
}