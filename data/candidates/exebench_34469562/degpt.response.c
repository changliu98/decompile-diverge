void swap(int *first, int *second)
{
    // Add the values of both pointers and store in xp
    *first = *first + *second;
    // Subtract the original value of yp from the new xp and store in yp
    *second = *first - *second;
    // Subtract the new value of yp from the new xp and store in xp
    *first = *first - *second;
}