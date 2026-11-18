void foo(long limit, long *target_ptr, long *source_ptr)
{
    // Base case: if n is not positive, do nothing
    if (0 < limit) {
        // Recursively call foo with n divided by 2
        foo(limit / 2, target_ptr, source_ptr);
        // Loop from 1 to n (inclusive)
        for (long counter = 1; counter <= limit; counter = counter + 1) {
            // Update the value pointed to by p by adding the value pointed to by q
            *target_ptr = *source_ptr + *target_ptr;
        }
    }
}